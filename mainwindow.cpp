#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

const QString SECRET_PASSWORD_ENCRYPT_KEY = "secret_key";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    writeAllPasswordsTopasswordsListWidget();

    databaseManager = DatabaseManager();
    crypto = Crypto();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPasswordPushButton_clicked()
{
    QTextEdit* newPasswordTextEdit = ui -> newPasswordTextEdit;
    QTextEdit* newPasswordTitleTextEdit = ui -> newPasswordTitleTextEdit;

    QString password = newPasswordTextEdit -> toPlainText();
    QString passwordTitle = newPasswordTitleTextEdit -> toPlainText();

    if(passwordTitle == "") {
        QMessageBox msgBox;

        msgBox.setText("Будь ласка, напишіть назву паролю");
        msgBox.exec();

        return;
    }
    if(password == "") {
        QMessageBox msgBox;

        msgBox.setText("Будь ласка, напишіть пароль");
        msgBox.exec();

        return;
    }
    PasswordItem passwordInDb = databaseManager.getPasswordByTitle(passwordTitle);

    if(passwordInDb.title == "") {
        ui -> passwordsListWidget -> addItem(passwordTitle);

        QString hash = crypto.encrypt(SECRET_PASSWORD_ENCRYPT_KEY, password);

        databaseManager.savePassword(passwordTitle, hash);
    } else {
        QMessageBox messageBox;

        messageBox.setText("Пароль з такою назвою вже існує");
        messageBox.exec();
    }
    newPasswordTextEdit -> setText("");
    newPasswordTitleTextEdit -> setText("");
}

void MainWindow::writeAllPasswordsTopasswordsListWidget()
{
    std::forward_list<QString> passwords = databaseManager.getAllPasswordsTitles();

    for(QString item : passwords) {
        ui -> passwordsListWidget -> addItem(item);
    }
}


void MainWindow::deletePasswordByTitle(QString title, QListWidgetItem* item) {
    delete item;
    databaseManager.deletePasswordByTitle(title);
}


void MainWindow::on_passwordsListWidget_itemClicked(QListWidgetItem *item)
{
    QString passwordTitle = item -> text();
    QMessageBox msgBox;

    QPushButton* deletePasswordBtn = new QPushButton("Видалити пароль");
    QPushButton* okButton = new QPushButton("Ok");

    connect(deletePasswordBtn, &QPushButton::clicked, this, [this, passwordTitle, item]{ deletePasswordByTitle(passwordTitle, item); });

    msgBox.addButton(okButton, QMessageBox::NoRole);
    msgBox.addButton(deletePasswordBtn, QMessageBox::NoRole);

    PasswordItem passwordItem = databaseManager.getPasswordByTitle(passwordTitle);

    msgBox.setWindowIconText(passwordTitle);
    msgBox.setText("Пароль: " + crypto.decrypt(SECRET_PASSWORD_ENCRYPT_KEY, passwordItem.password));
    msgBox.exec();
}



