#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseManager : public QObject{
    public:
        DatabaseManager(QObject *parent = 0);
        ~DatabaseManager();

    public:
        bool openDB();
        bool closeDB();
        bool createTable(QString table_name);
        bool insertElement(QString table_name, QString clave, QString palabra);
        bool getAnagramas(QString idioma, QString clave, QStringList *anagramas);
        QSqlError lastError();

    private:
        QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
