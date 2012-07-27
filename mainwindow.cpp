#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database.openDB();
    //create_lemario();
    //database.createTable();
}

MainWindow::~MainWindow(){
    database.closeDB();
    delete ui;
}

void MainWindow::word_to_key(QString *palabra){
    qSort(palabra->begin(), palabra->end());
}

void MainWindow::on_search_Button_clicked(){
    ui->plainTextEdit->clear();

    QString palabra = ui->lineEdit_palabraclave->text();
    QString clave = palabra;
    word_to_key(&clave);
    qDebug()<<palabra;
    qDebug()<<clave;
    QStringList anagramas;
    database.getAnagramas("es",clave,&anagramas);
    view_result(palabra, anagramas);
    qDebug()<<anagramas;
}

void MainWindow::create_lemario(){
    //Open the file for reading and set the text stream to read, from the file.
    QFile file_for_reading("D:\\Users\\Albert\\Desktop\\lemari_cat.txt");
    file_for_reading.open(QIODevice::ReadOnly);
    QTextStream text_stream_for_reading(&file_for_reading);

    int i=1;

    //read line
    while(!text_stream_for_reading.atEnd()){
        QString palabra = text_stream_for_reading.readLine(70);
        QString clave = palabra;
        word_to_key(&clave);
        if(database.insertElement(clave,palabra)){
        i++;
        }
    }

    qDebug()<<i;

    //close the file
    file_for_reading.close();
}

void MainWindow::view_result(QString palabra, QStringList anagramas){
    QString text;

    if(anagramas.isEmpty()){
        text="No existen anagramas para \"";
        text += palabra+"\"";
    }
    else{
        text="Los anagramas para \"";
        text += palabra;
        text += "\" son: \n";

        for(int i=0; i<anagramas.length(); i++){
            text += anagramas.at(i)+"\n";
        }
    }

    ui->plainTextEdit->appendPlainText(text);

}
