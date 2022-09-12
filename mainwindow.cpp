#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QInputDialog>
#include <QListWidget>
#include <QIcon>

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


void MainWindow::on_pushButton_add_clicked()
{
    QListWidgetItem* items = new QListWidgetItem(QIcon(":logo/new_lang.png"),
    QInputDialog::getText(this,"add lang","Programming language"));
    ui->listWidget->addItem(items);
}

void MainWindow::on_pushButton_del_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_checkBox_stateChanged(int arg)
{
    if (arg)
    {
        ui->listWidget->setViewMode(QListWidget::IconMode);
    }
    else
    {
        ui->listWidget->setViewMode(QListWidget::ListMode);
    }
}