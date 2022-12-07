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
    double x1,x2,d;

    double a = ui->lineEdit_a->text().toInt();
    double b = ui->lineEdit_b->text().toInt();
    double c = ui->lineEdit_c->text().toInt();

        if(a == 0)
        {
            x1 = -c/b;
            ui->lineEdit_x1->setText(QString(" %1").arg(x1));
        }
        else
        {
                d = qPow(b, 2) - 4 * a * c;
                if(d < 0)
                {
                    ui->lineEdit_x1->setText(QString(" It is impossible to calculate the root !"));
                    return;
                }

                    x1 = (-b - qSqrt(d)) / 2 * a;

                if(d == 0) ui ->lineEdit_x1->setText(QString(" %1").arg(x1));
                else
                {
                    x2 = (-b + qSqrt(d)) / 2 * a;
                    ui->lineEdit_x1->setText(QString(" %1").arg(x1));
                    ui->lineEdit_x2->setText(QString(" %2").arg(x2));
                }

        }
}
