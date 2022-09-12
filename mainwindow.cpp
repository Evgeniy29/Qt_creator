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
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    auto spec = Spec.Get_Spec(arg1.toUpper());

         if(spec.has_value())
            {
                ui->lineEdit->setText(Spec.Spec(arg1, spec.value()));
            }
}
