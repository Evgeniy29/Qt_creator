#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator LanguageTranslator;
    a.installTranslator(&LanguageTranslator);
    MainWindow w;
    w.show();
    return a.exec();
}
