#include <QApplication>
#include "mainwindow.h"

// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication  app(argc, argv);
    Download d;
    d.resize(300, 200);
    d.show();


    return app.exec();
}
