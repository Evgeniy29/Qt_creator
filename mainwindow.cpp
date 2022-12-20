#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "explorer.h"
#include <QTranslator>
#include <QLibraryInfo>
#include <QEvent>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


       this->aDirList = new QFileInfoList();

       this->model = new QViewExplorer();

       this->currentFolder = QDir(QDir::currentPath());

       this->model->getFolderList(this->currentFolder.absolutePath(),this->aDirList);

       this->ui->lineEdit->setText(QDir::currentPath());

       this->ui->listView->setModel(model);

       this->ui->listView->setWordWrap(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeTranslator(QString postfix)
{
    QApplication::removeTranslator(LanguageTranslator);
    LanguageTranslator = new QTranslator(this);
    LanguageTranslator->load(QApplication::applicationName() + "_" + postfix);
    QApplication::installTranslator(LanguageTranslator);
}

void MainWindow::changeEvent(QEvent *event)
{
    setWindowTitle(tr("Текстовый редактор"));

    if(event->type() == QEvent::LanguageChange)
        {
            ui->menuFile->setTitle(tr("Файл"));
            ui->menuHelp->setTitle(tr("Помощь"));
            ui->menuLanguage->setTitle(tr("Язык"));
            ui->actionRussian->setText(tr("Русский"));
            ui->actionEnglish->setText(tr("Английский"));
            ui->actionNew->setText(tr("Новый"));
            ui->actionOpen->setText(tr("Открыть"));
            ui->actionOpen_read_only->setText(tr("Только для чтения"));
            ui->actionSave->setText(tr("Сохранить"));
            ui->actionFAQ->setText(tr("Справка"));
            ui->actionExit->setText(tr("Выход"));

        }
            else
        {

            QMainWindow::changeEvent(event);
        }
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

void MainWindow::on_actionNew_triggered()
{
    current_file.clear();
    ui->textEdit->setPlainText(QString());
}

void MainWindow::on_actionOpen_read_only_triggered()
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
    ui->textEdit->setReadOnly(true);
    file.close();
}

void MainWindow::on_actionRussian_triggered()
{
    changeTranslator("ru");
}

void MainWindow::on_actionEnglish_triggered()
{
    changeTranslator("en");
}



void MainWindow::on_pushButton_clicked()
{
    currentFolder.cdUp();

        this->ui->lineEdit->setText(currentFolder.absolutePath());
        model->getFolderList(currentFolder.absolutePath(),this->aDirList);
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if (this->aDirList->at(index.row()).isDir())
        {
            QString tmp = this->aDirList->at(index.row()).absoluteFilePath();
            model->getFolderList(this->aDirList->at(index.row()).absoluteFilePath(),this->aDirList);
            this->ui->lineEdit->setText(tmp);
        } else {
            QDesktopServices::openUrl(QUrl(this->aDirList->at(index.row()).absoluteFilePath()));
        }
}

void MainWindow::on_actionDark_style_triggered()
{
    QPalette darkPalette;

            darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
            darkPalette.setColor(QPalette::WindowText, Qt::white);
            darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
            darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
            darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
            darkPalette.setColor(QPalette::ToolTipText, Qt::white);
            darkPalette.setColor(QPalette::Text, Qt::white);
            darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
            darkPalette.setColor(QPalette::ButtonText, Qt::white);
            darkPalette.setColor(QPalette::BrightText, Qt::red);
            darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
}

void MainWindow::on_actionLight_style_triggered()
{
    qApp->setPalette(style()->standardPalette());
}
