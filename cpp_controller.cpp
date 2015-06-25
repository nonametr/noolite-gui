#include "cpp_controller.h"
#include "data_object.h"

#include <QDebug>
#include <QQmlContext>

CPPController::CPPController()
{
    ua_translator.load("ukrainian.qm", ":/translations");
    en_translator.load("english.qm", ":/translations");
    ru_translator.load("russian.qm", ":/translations");

    translator_map =
    {
        {LANG_ENGLISH,      &en_translator},
        {LANG_RUSSIAN,      &ru_translator},
        {LANG_UKRAINIAN,    &ua_translator}
    };

    lang_map =
    {
        {LANG_ENGLISH,      "English"},
        {LANG_RUSSIAN,      "Russian"},
        {LANG_UKRAINIAN,    "Ukrainian"}
    };
}

void CPPController::setEngine(QQmlApplicationEngine &l_engine)
{
    engine = &l_engine;
}

void CPPController::onLanguageChanged(const int new_lang)
{
    setLanguage(new_lang);
    reloadWindow();
}

void CPPController::reloadWindow()
{
    engine->clearComponentCache();

    QQmlContext *context = engine->rootContext();
    context->setContextProperty("modelConsoles", QVariant::fromValue(_createModelConsoles()));

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void CPPController::setLanguage(const int new_lang)
{
    qDebug() << "Switching language to " << lang_map[new_lang].toStdString().c_str();

    auto it_translation = translator_map.find(new_lang);
    if(it_translation == translator_map.end())
    {
        qDebug() << "Unsupported language";
        return;
    }

    qApp->removeTranslator(current_translator);
    current_translator = it_translation->second;
    qApp->installTranslator(current_translator);
}

QList<QObject*> CPPController::_createModelConsoles()
{
    QList<QObject*> consolesList;
    for(uint i = 0; i < 64; ++i)
    {
        std::string channel = QObject::tr("Channel #").toStdString() + std::to_string(i);
        consolesList.append(new DataObject(channel.c_str()));
    }

    return consolesList;
}
