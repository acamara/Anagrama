#include "databasemanager.h"
#include <QtGui/QApplication>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent){

}

DatabaseManager::~DatabaseManager(){

}

bool DatabaseManager::openDB(){
    bool ret = true;
    // Get the directory that stores the application data
    QDir dir = QDir::currentPath();
    qDebug()<<dir.absolutePath();

    //Create the file path to the database
    QString dbName = dir.filePath("lemario.db");
    qDebug()<<dbName;

    //QSqlDatabase instantiate and use dbName as a route to the database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);    //<--Línea modificada

    //Open the database and displays a warning in case of failure
    if (!db.open()) {
      QMessageBox::critical(0, qApp->tr("Error al abrir el Lemario"),
      qApp->tr("Ha sido imposible abrir el Lemario"),
      QMessageBox::Ok);
      ret = false;
    }

    return ret;
}

bool DatabaseManager::closeDB(){
    bool ret = false;
    // Close database
    db.close();
    if(!db.isOpen()){
        ret = true;
    }
    return ret;
}

QSqlError DatabaseManager::lastError(){
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::createTable(QString table_name){
    bool ret = false;

    if (db.isOpen()){
        QSqlQuery query;
        ret = query.exec(QString("create table if not exists %1 "
                         "(id integer primary key autoincrement, "
                         "clave varchar(50), "
                         "palabra varchar(50))").arg(table_name));
    }

    return ret;
}

bool DatabaseManager::insertElement(QString table_name, QString key, QString word){
    bool ret = false;

    if (db.isOpen()){
        QSqlQuery query;
        ret = query.exec(QString("INSERT INTO %1 VALUES(NULL,'%2','%3')").arg(table_name).arg(key).arg(word));
    }

    return ret;
}

bool DatabaseManager::getAnagramas(QString language, QString key, QStringList *anagramas){
    bool ret = false;

    QSqlQuery query(QString("SELECT palabra FROM %1 WHERE clave = '%2'").arg(language).arg(key));

    while(query.next()){
        anagramas->append(query.value(0).toString());
        ret = true;
    }

    return ret;
}
