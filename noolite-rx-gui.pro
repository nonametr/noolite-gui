TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    data_object.cpp \
    cpp_controller.cpp

lupdate_only {
SOURCES = main.qml \
          main.cpp \
          data_object.cpp \
          MainForm.ui.qml
}

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    data_object.h \
    cpp_controller.h

TRANSLATIONS = translations/english.ts \
               translations/ukrainian.ts \
               translations/russian.ts
