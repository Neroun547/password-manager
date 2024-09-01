#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include <QListWidgetItem>
#include "crypto.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addPasswordPushButton_clicked();
    void writeAllPasswordsTopasswordsListWidget();
    void on_passwordsListWidget_itemClicked(QListWidgetItem *item);
    void deletePasswordByTitle(QString title, QListWidgetItem* item);

private:
    Ui::MainWindow *ui;
    DatabaseManager databaseManager;
    Crypto crypto;
};
#endif // MAINWINDOW_H
