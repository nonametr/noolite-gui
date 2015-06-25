#ifndef CPPCONTROLLER_H
#define CPPCONTROLLER_H

#include <QObject>
#include <QApplication>
#include <QTranslator>
#include <QQmlApplicationEngine>

#include <map>
using namespace std;

#define LANG_ENGLISH 1
#define LANG_RUSSIAN 2
#define LANG_UKRAINIAN 3

class CPPController : public QObject
{
   Q_OBJECT

public:
   CPPController();
   virtual ~CPPController() override = default;

   void setLanguage(const int new_lang);
   void reloadWindow();
   void setEngine(QQmlApplicationEngine &l_engine);

public slots:
   void onLanguageChanged(const int new_lang);

private:
   QTranslator en_translator;
   QTranslator ru_translator;
   QTranslator ua_translator;

   QTranslator *current_translator = nullptr;
   map<int, QTranslator*> translator_map;
   map<int, QString> lang_map;

   QQmlApplicationEngine *engine = nullptr;

   QList<QObject*> _createModelConsoles();
};

#endif // CPPCONTROLLER_H
