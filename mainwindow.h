#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void create_lemario(QString idioma);
    void on_search_Button_clicked();
    void word_to_key(QString *palabra);
    void view_result(QString palabra, QStringList anagramas);

private:
    Ui::MainWindow *ui;
    DatabaseManager database;
};

#endif // MAINWINDOW_H
