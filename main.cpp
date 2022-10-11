#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QObject>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<MainWindow>("TableModel", 0, 1, "TableModel");

    QQmlApplicationEngine engine;
    MainWindow tableModel;
    engine.rootContext()->setContextProperty("tableModel", &tableModel);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
