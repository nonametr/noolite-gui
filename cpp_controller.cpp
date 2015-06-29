#include "cpp_controller.h"

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
    _setLanguage(config.getLang());
}

void CPPController::onLanguageChanged(const int new_lang)
{
    _setLanguage(new_lang);
    reloadWindow();
    config.setLang(new_lang);
}

void CPPController::reloadWindow()
{
    engine->clearComponentCache();

    QQmlContext *context = engine->rootContext();
    ConsolesModel *model = _createModelConsoles();
    context->setContextProperty("modelConsoles", model);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void CPPController::_setLanguage(const int new_lang)
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

ConsolesModel *CPPController::_createModelConsoles()
{
    ConsolesModel *model = new ConsolesModel;

    for(uint i = 0; i < 64; ++i)
    {
        QString channel = QObject::tr("Channel #") + QString::number(i);
        model->addConsole(Console(channel, i));
    }

    return model;
}
