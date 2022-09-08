#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

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


void MainWindow::on_commandLinkButton_clicked()
{
    double a = ui->lineEdit->text().toInt();
       double b = ui->lineEdit_2->text().toInt();

       double c = -1;
       double angle = ui->lineEdit_3->text().toInt();

       if(a != 0 && b != 0 && angle != 0) {
           c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(angle /180 * M_PI));
           if(ui->checkBox->isChecked()){
               c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(angle));
           }
           ui->lineEdit_4->setText(QString(" => %1").arg(c));
       }else {
           ui->lineEdit_4->setText(QString("Введите исходные данные заново!"));
       }
}
