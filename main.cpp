#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "data_object.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QList<QObject*> consolesList;
    for(uint i = 0; i < 64; ++i)
    {
        std::string channel = std::string("Channel #") + std::to_string(i);
        consolesList.append(new DataObject(channel.c_str()));
    }

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("modelConsoles", QVariant::fromValue(consolesList));

    return app.exec();
}
