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
    //QString table_name = "en";
    //create_lemario(table_name);
    //database.createTable(table_name);
}

MainWindow::~MainWindow(){
    database.closeDB();
    delete ui;
}

void MainWindow::word_to_key(QString *word){
    qSort(word->begin(), word->end());
}

void MainWindow::on_search_Button_clicked(){
    ui->plainTextEdit->clear();

    QString word = ui->lineEdit_palabraclave->text();
    QString key = word;

    word_to_key(&key);
    //qDebug()<<word;
    //qDebug()<<key;

    QStringList anagramas;
    database.getAnagramas(ui->comboBox_idioma->currentText(),key,&anagramas);
    view_result(word, anagramas);
    //qDebug()<<anagramas;
}

void MainWindow::create_lemario(QString language){
    //Open the file for reading and set the text stream to read, from the file.
    QFile file_for_reading("D:\\Users\\Albert\\Desktop\\Albert\\Programación\\Qt\\Anagrama\\Lemari\\lemari_en.txt");
    file_for_reading.open(QIODevice::ReadOnly);
    QTextStream text_stream_for_reading(&file_for_reading);

    int i=1;

    //read line
    while(!text_stream_for_reading.atEnd()){
        QString word = text_stream_for_reading.readLine(70);
        QString key = word;
        word_to_key(&key);
        if(database.insertElement(language,key,word)){
        i++;
        }
    }

    qDebug()<<i;

    //close the file
    file_for_reading.close();
}

void MainWindow::view_result(QString word, QStringList anagramas){
    QString text;

    if(anagramas.isEmpty()){
        text="No existen anagramas para \"";
        text += word+"\"";
    }
    else{
        text="Los anagramas para \"";
        text += word;
        text += "\" son: \n \n";

        for(int i=0; i<anagramas.length(); i++){
            text += anagramas.at(i)+"\n";
        }
    }

    ui->plainTextEdit->appendPlainText(text);

}
