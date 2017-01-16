#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QTranslator>
#include <QIcon>

#include <stdio.h>

#include "cpp_controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/rx.png"));

    QString arg_1 = argc > 1 ? QCoreApplication::arguments().at(1) : "";
    if(arg_1 == "-tx" && argc >= 3)
    {
        Tx1132 tx;

        QString arg_2 = QCoreApplication::arguments().at(2);
        QString arg_3 = QCoreApplication::arguments().at(3);
        QString arg_4 = argc >= 5 ? QCoreApplication::arguments().at(4) : 0;
        QString arg_5 = argc >= 6 ? QCoreApplication::arguments().at(5) : 0;
        QString arg_6 = argc >= 7 ? QCoreApplication::arguments().at(6) : 0;

        return tx.execute(static_cast<TX_ACTION>(arg_2.toInt()),
                          static_cast<u_char>(arg_3.toInt()),
                          static_cast<u_char>(arg_4.toInt()),
                          static_cast<u_char>(arg_5.toInt()),
                          static_cast<u_char>(arg_6.toInt()));
    }

    CPPController cpp_controller;

    cpp_controller.initGUI();
    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("cpp_controller", &cpp_controller);

    cpp_controller.setEngine(engine);
    cpp_controller.loadWindow();
    return app.exec();
}
