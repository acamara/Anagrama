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
    bool correcte = true;
    //Obtenemos el directorio en el que se almacenan los datos de las aplicaciones
    QDir dir = QDir::currentPath();
    qDebug()<<dir.absolutePath();

    //Creamos la ruta al fichero de la base de datos
    QString dbName = dir.filePath("lemario.db");
    qDebug()<<dbName;

    //Instanciamos QSqlDatabase y utilizamos dbName como ruta
    //al archivo de la base de datos
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);    //<--Línea modificada

    //Abre la base de datos y muestra un aviso en caso de error
    if (!db.open()) {
      QMessageBox::critical(0, qApp->tr("Error al abrir el Lemario"),
      qApp->tr("Ha sido imposible abrir el Lemario"),
      QMessageBox::Ok);
      correcte = false;
    }

    return correcte;
}

bool DatabaseManager::closeDB(){
    // Close database
    db.close();
}

QSqlError DatabaseManager::lastError(){
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::createTable(){
    // Create table "es"
    bool ret = false;

    if (db.isOpen()){
        QSqlQuery query;
        ret = query.exec("create table if not exists cat "
                         "(id integer primary key autoincrement, "
                         "clave varchar(50), "
                         "palabra varchar(50))");
    }

    return ret;
}

bool DatabaseManager::insertElement(QString clave, QString palabra){
    bool ret = false;

    if (db.isOpen()){
        QSqlQuery query;
        ret = query.exec(QString("INSERT INTO cat VALUES(NULL,'%1','%2')").arg(clave).arg(palabra));
    }

    return ret;
}

bool DatabaseManager::getAnagramas(QString idioma, QString clave, QStringList *anagramas){
    bool ret = false;

    QSqlQuery query(QString("SELECT palabra FROM %1 WHERE clave = '%2'").arg(idioma).arg(clave));

    while(query.next()){
        anagramas->append(query.value(0).toString());
        ret = true;
    }

    return ret;
}
