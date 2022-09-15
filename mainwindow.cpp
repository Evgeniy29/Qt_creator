#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"open file");
    QFile file(filename);
    current_file =filename;
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,"warning","Cannot open file : " +file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text= in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save ");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"warning","Cannot save file : " +file.errorString());
        return;
    }
    current_file =filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<< text;
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionFAQ_triggered()
{
   //QMessageBox::information(this,"help","Справка о программе text editor");
QDesktopServices::openUrl(QUrl("file:///C:/Users/John/Desktop/GeekBrians/Qt/Lesson_3/build-text_editor-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/help.txt",QUrl::TolerantMode));
}
