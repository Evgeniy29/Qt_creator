#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTranslator>
#include <QEvent>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionFAQ_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_read_only_triggered();


    void on_actionEnglish_triggered();

    void on_actionRussian_triggered();

private:

    void changeTranslator(QString postfix);
    void changeEvent(QEvent *event) ;

private:
    Ui::MainWindow *ui;
    QString current_file="";
    QTranslator* LanguageTranslator;
};
#endif // MAINWINDOW_H
