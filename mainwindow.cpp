#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    ui->plainTextEdit_2->moveCursor(QTextCursor::End);
    ui->plainTextEdit_2->insertPlainText(text);
    ui->plainTextEdit_2->moveCursor(QTextCursor::End);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_2->insertPlainText(text);
}

void MainWindow::on_pushButton_3_clicked()
{
    QTextEdit text_html;
    text_html.setHtml("<font color='red'>Hello</font>");
    text_html.show();
}
