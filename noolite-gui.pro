TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    cpp_controller.cpp \
    config.cpp \
    formater.cpp \
    noolite-trx/tx1132.cpp \
    noolite-trx/rx2164.cpp \
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
    noolite-trx/tx1132.h \
    noolite-trx/rx2164.h \
    rx-gui/rx_channels_model.h \
    rx-gui/rx_channel_cfg_model.h \
    rx-gui/rx_status_model.h \
    rx-gui/rx_gui_model.h \
    tx-gui/tx_gui_model.h \
    tx-gui/tx_channels_model.h

TRANSLATIONS = translations/english.ts \
               translations/ukrainian.ts \
               translations/russian.ts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../opt/local/lib/release/ -lusb-1.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../opt/local/lib/debug/ -lusb-1.0
else:unix: LIBS += -L$$PWD/../../../../opt/local/lib/ -lusb-1.0

INCLUDEPATH += $$PWD/../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../opt/local/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../opt/local/lib/release/libusb-1.0.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../opt/local/lib/debug/libusb-1.0.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../opt/local/lib/release/usb-1.0.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../opt/local/lib/debug/usb-1.0.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../opt/local/lib/libusb-1.0.a
