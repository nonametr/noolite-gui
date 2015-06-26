#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QIcon>

#include <stdio.h>

#include "cpp_controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/rx.png"));

    CPPController cpp_controller;
    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("cpp_controller", &cpp_controller);

    cpp_controller.setEngine(engine);
    cpp_controller.reloadWindow();

    return app.exec();
}
