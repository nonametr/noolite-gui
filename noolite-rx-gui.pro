TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    cpp_controller.cpp \
    config.cpp \
    consoles_model.cpp

lupdate_only {
SOURCES = main.qml \
          main.cpp \
          config.cpp \
          cpp_controller.cpp \
          MainForm.ui.qml
}

RESOURCES += qml.qrc

ICON = rx.icns#it's for OSX

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    cpp_controller.h \
    config.h \
    consoles_model.h

TRANSLATIONS = translations/english.ts \
               translations/ukrainian.ts \
               translations/russian.ts
