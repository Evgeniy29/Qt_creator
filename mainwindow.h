#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool createConection();
    bool createTable();
    bool insertRec(QString task="",QString data="",QString progress="");
    void printTable();
    QSqlDatabase db;
    QSqlTableModel* model;
    QTableView* view;
};
#endif // MAINWINDOW_H
