TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    cpp_controller.cpp \
    config.cpp \
    ../noolite-rx/rx2164.cpp \
    channels_model.cpp \
    status_model.cpp \
    formater.cpp \
    channel_actions_model.cpp

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
    channels_model.h \
    ../noolite-rx/rx2164.h \
    status_model.h \
    formater.h \
    channel_actions_model.h

TRANSLATIONS = translations/english.ts \
               translations/ukrainian.ts \
               translations/russian.ts

LIBS += -lusb-1.0
