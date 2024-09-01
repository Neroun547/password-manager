#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <forward_list>

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

struct PasswordItem
{
    QString title;
    QString password;
};

class DatabaseManager
{

public:
    QSqlDatabase db;
    DatabaseManager();

    std::forward_list<QString> getAllPasswordsTitles();
    void savePassword(QString title, QString passwordHash);
    PasswordItem getPasswordByTitle(QString title);
    void deletePasswordByTitle(QString title);
};

#endif // DATABASEMANAGER_H

