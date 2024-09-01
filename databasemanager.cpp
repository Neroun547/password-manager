#include "databasemanager.h"
#include <forward_list>

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("passwords.sqlite");
}

std::forward_list<QString> DatabaseManager::getAllPasswordsTitles() {
    std::forward_list<QString> result;

    db.open();
    QSqlQuery q;

    q.exec("SELECT * FROM passwords");

    while(q.next()) {
        result.push_front(q.value(0).toString());
    }
    q.clear();
    db.close();

    return result;
}

void DatabaseManager::savePassword(QString title, QString passwordHash) {
    QString sqlQuery = "insert into passwords values (";

    sqlQuery += "'";
    sqlQuery += title;
    sqlQuery += "', '";
    sqlQuery += passwordHash;
    sqlQuery += "');";

    db.open();

    QSqlQuery q;
    q.exec(sqlQuery);

    q.clear();
    db.close();
}

PasswordItem DatabaseManager::getPasswordByTitle(QString title) {
    PasswordItem result;

    db.open();
    QSqlQuery q;

    QString sqlQuery = "SELECT * FROM passwords where title = ";

    sqlQuery += "'";
    sqlQuery += title;
    sqlQuery += "';";

    q.exec(sqlQuery);

    while(q.next()) {
        result.title = q.value(0).toString();
        result.password = q.value(1).toString();
    }
    q.clear();
    db.close();

    return result;
}

void DatabaseManager::deletePasswordByTitle(QString title) {
    db.open();

    QString sqlQuery = "delete from passwords where title = ";

    sqlQuery += "'";
    sqlQuery += title;
    sqlQuery += "'";
    sqlQuery += ";";

    QSqlQuery q;

    q.exec(sqlQuery);

    q.clear();
    db.close();
}
