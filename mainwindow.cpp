#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!createConection()) return;

    if(!createTable()) return;
   insertRec("Task_1", "01.01.2020" , "1");
   insertRec("Task_2", "01.01.2021" , "2");
   insertRec("Task_3", "01.01.2022" , "3");
   printTable();
   view = new QTableView(this);
   setCentralWidget(view);

   model=new QSqlTableModel(this);

   model->setTable("tasks");
   model->select();
   model->setEditStrategy(QSqlTableModel::EditStrategy::OnFieldChange);
   view->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::createConection()
{
     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("tasks.db");
     if(!db.open())
     {
         qDebug()<< "Can't open db";
         return false;
     }
     return true;
}

bool MainWindow::createTable()
{
    QSqlQuery query;
    QString s = "CREATE TABLE tasks ("
                "id INTEGER PRIMARY KEY NOT NULL,"
                "task VARCHAR(15),"
                "data VARCHAR(15),"
                "progress VARCHAR(15) );";
    if(!query.exec(s)){
        qDebug()<< "Can't create table";
        return false;
    }
    return true;
}

bool MainWindow::insertRec(QString task, QString data, QString progress)
{
    QSqlQuery query;
    QString s = "INSERT INTO tasks (task, data, progress) "
                "VALUES('%1', '%2' , '%3');";
   QString q = s.arg(task).arg(data).arg(progress);
   if(!query.exec(q)){
       qDebug()<<"Can't insert";
       return false;
   }
   return true;
}

void MainWindow::printTable()
{
    QStringList tables =db.tables();
    for(QString& table: tables)
    {
        qDebug()<<table;
    }
    QSqlQuery query;
    if(!query.exec("SELECT * FROM tasks;")){
        qDebug()<<"Can't readtabl";
    }
    QSqlRecord rec =query.record();
    while (query.next()) {
        qDebug()<< query.value(rec.indexOf("id")).toInt()<<"\t"<<
                   query.value(rec.indexOf("task")).toString()<<"\t"<<
                   query.value(rec.indexOf("data")).toString()<<"\t"<<
                   query.value(rec.indexOf("progress")).toString();

    }

}



