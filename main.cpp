#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QDebug>
#include <QIcon>

#include "cpp_controller.h"

int getLocaleLanguage()
{
    QLocale::Country country = QLocale::system().country();

    qDebug() << "Selecting language for "<< QLocale::system().nativeCountryName();

    switch(country)
    {
    case QLocale::Ukraine:
        return LANG_UKRAINIAN;
    case QLocale::Russia:
    case QLocale::Belarus:
    case QLocale::Kazakhstan:
    case QLocale::Latvia:
    case QLocale::Lithuania:
    case QLocale::Turkmenistan:
    case QLocale::Kirghiz:
    case QLocale::Moldova:
    case QLocale::Uzbekistan:
    case QLocale::Azerbaijani:
    case QLocale::ArmenianScript:
    case QLocale::Georgia:
        return LANG_RUSSIAN;
    default:
        return LANG_ENGLISH;
    }

    return LANG_ENGLISH;
}

int main(int argc, char *argv[])
{   
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/rx.png"));

    CPPController cpp_controller;
    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("cpp_controller", &cpp_controller);

    cpp_controller.setEngine(engine);
    cpp_controller.setLanguage(getLocaleLanguage());
    cpp_controller.reloadWindow();

    return app.exec();
}
