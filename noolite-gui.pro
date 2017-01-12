TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    cpp_controller.cpp \
    config.cpp \
    formater.cpp \
    noolite-tx/tx1132.cpp \
    noolite-rx/rx2164.cpp \
    rx-gui/rx_channels_model.cpp \
    rx-gui/rx_channel_cfg_model.cpp \
    rx-gui/rx_status_model.cpp \
    rx-gui/rx_gui_model.cpp \
    tx-gui/tx_gui_model.cpp \
    tx-gui/tx_channels_model.cpp

lupdate_only {
SOURCES = rx-gui/RxTool.qml \
          rx-gui/RxToolWindow.ui.qml \
          tx-gui/TxTool.qml \
          tx-gui/TxToolWindow.ui.qml \
          main.cpp \
          config.cpp \
          cpp_controller.cpp
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
    formater.h \
    noolite-tx/tx1132.h \
    noolite-rx/rx2164.h \
    rx-gui/rx_channels_model.h \
    rx-gui/rx_channel_cfg_model.h \
    rx-gui/rx_status_model.h \
    rx-gui/rx_gui_model.h \
    tx-gui/tx_gui_model.h \
    tx-gui/tx_channels_model.h

TRANSLATIONS = translations/english.ts \
               translations/ukrainian.ts \
               translations/russian.ts

LIBS += -lusb-1.0
