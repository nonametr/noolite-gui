import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {

    id: nooliteToolRX
    title: qsTr("RX Tool")
    x: rx_model_gui.rxX
    y: rx_model_gui.rxY
    width: rx_model_gui.rxWidth
    height: rx_model_gui.rxHeight
    minimumWidth: 900
    minimumHeight: 480
    onXChanged: if(rx_model_gui.rxX !== nooliteToolRX.x) rx_model_gui.rxX = nooliteToolRX.x
    onYChanged: if(rx_model_gui.rxY !== nooliteToolRX.y) rx_model_gui.rxY = nooliteToolRX.y
    onHeightChanged: if(rx_model_gui.rxHeight !== nooliteToolRX.height) rx_model_gui.rxHeight = nooliteToolRX.height
    onWidthChanged: if(rx_model_gui.rxWidth !== nooliteToolRX.width) rx_model_gui.rxWidth = nooliteToolRX.width
    visible: true

    property int lang_english : 1
    property int lang_russian : 2
    property int lang_ukrainian : 3

    RxToolWindow {
        id: rxTool
        anchors.fill: parent

        settingsButton.onClicked: messageDialog.show(qsTr("This functionality not Implemented!"));
        exitButton.onClicked: Qt.quit();
        openScriptButton.onClicked: fileDialog.open()
        buttonBind.onClicked: cpp_controller.onBind(listViewConsoles.currentIndex)
        buttonUnbind.onClicked: cpp_controller.onUnbind(listViewConsoles.currentIndex)
        switchForwardData.onCheckedChanged: {
            rx_model_channel_cfg.fw = switchForwardData.checked
            //restore binding
            switchForwardData.checked = Qt.binding(function () {
                        return rx_model_channel_cfg.fw;
                    });
        }
        switchForwardExtData.onCheckedChanged: {
            rx_model_channel_cfg.fwExt = switchForwardExtData.checked
            //restore binding
            switchForwardExtData.checked = Qt.binding(function () {
                        return rx_model_channel_cfg.fwExt;
                    });
        }
        comboBoxAction.onCurrentIndexChanged:
        {
            cpp_controller.onChannelSelect(listViewConsoles.currentIndex, comboBoxAction.currentIndex);
        }
        buttonSave.onClicked:
        {
            cpp_controller.onSave()
        }

        listViewConsoles.delegate: Item {
            property var view: ListView.view
            property var isCurrent: ListView.isCurrentItem
            property var currentItem: ListView.currentItem

            width: view.width
            height: 40

            Rectangle {
                anchors.margins: 5
                anchors.fill: parent
                border {
                    color: "black"
                    width: 1
                }

                TextInput {
                    id: listItemTextInput
                    activeFocusOnPress: false
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    onEditingFinished: {
                        rx_model_channels.setProperty(model.index, "text", text)
                    }
                    text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onDoubleClicked: {
                        listItemTextInput.forceActiveFocus()
                        view.currentIndex = -1
                    }
                    onClicked: {
                        if(mouse.button === Qt.LeftButton)
                        {
                            parent.forceActiveFocus(Qt.MouseFocusReason)
                            view.currentIndex = model.index
                            cpp_controller.onChannelSelect(view.currentIndex, 0);
                        }
                        else if(mouse.button === Qt.RightButton)
                        {
                            view.currentIndex = model.index
                            listViewContextMenu.popup()
                        }
                    }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a script file"
        nameFilters: [ "Script files (*.sh *.php *.py *.pl *.ps1 *.bat)", "All files (*)" ]
        onAccepted: {
            console.log("Selected script => " + fileDialog.fileUrls)
            var path = fileDialog.fileUrl.toString();
            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            path = "/" + decodeURIComponent(path);
            mainForm.textFieldScriptPath.text = path
        }
        onRejected: {
            console.log("File selection canceled")
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Menu")

            Menu {
                title: qsTr("&Language")

                MenuItem {
                    text: qsTr("&English")
                    onTriggered: {
                        cpp_controller.onLanguageChanged(lang_english)
                        close()
                    }
                }
                MenuItem {
                    text: qsTr("&Ukrainian")
                    onTriggered: {
                        cpp_controller.onLanguageChanged(lang_ukrainian)
                        close()
                    }
                }
                MenuItem {
                    text: qsTr("&Russian")
                    onTriggered: {
                        cpp_controller.onLanguageChanged(lang_russian)
                        close()
                    }
                }
            }

            Menu {
                title: qsTr("&Tool")

                MenuItem {
                    text: qsTr("&RxTool")
                    onTriggered: {
                        cpp_controller.onToolChanged("qrc:/rx-gui/RxTool.qml")
                        close()
                    }
                }
                MenuItem {
                    text: qsTr("&TxTool")
                    onTriggered: {
                        cpp_controller.onToolChanged("qrc:/tx-gui/TxTool.qml")
                        close()
                    }
                }
            }

            MenuSeparator { }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    Menu {
        id: listViewContextMenu
        MenuItem {
            text: qsTr('Edit')
        }
        MenuItem {
            text: qsTr('Reset')
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
