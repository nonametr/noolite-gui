import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {

    id: nooliteToolTX
    title: qsTr("TX Tool")
    x: tx_model_gui.txX
    y: tx_model_gui.txY
    width: tx_model_gui.txWidth
    height: tx_model_gui.txHeight
    minimumWidth: 500
    minimumHeight: 420
    onXChanged: if(tx_model_gui.txX !== nooliteToolTX.x) tx_model_gui.txX = nooliteToolTX.x
    onYChanged: if(tx_model_gui.txY !== nooliteToolTX.y) tx_model_gui.txY = nooliteToolTX.y
    onHeightChanged: if(tx_model_gui.txHeight !== nooliteToolTX.height) tx_model_gui.txHeight = nooliteToolTX.height
    onWidthChanged: if(tx_model_gui.txWidth !== nooliteToolTX.width) tx_model_gui.txWidth = nooliteToolTX.width
    visible: true

    property int lang_english : 1
    property int lang_russian : 2
    property int lang_ukrainian : 3

    TxToolWindow {
        id: txTool
        anchors.fill: parent

        buttonExecute.onClicked: {
            switch(comboBoxAction.currentIndex)
            {
                case 3:
                    cpp_controller.onTxExecute(listViewConsoles.currentIndex, comboBoxAction.currentIndex, lvlSpinBox.value, 0, 0);
                    break;
                case 13:
                    cpp_controller.onTxExecute(listViewConsoles.currentIndex, comboBoxAction.currentIndex, rSpinBox.value, gSpinBox.value, bSpinBox.value);
                    break;
                default:
                    cpp_controller.onTxExecute(listViewConsoles.currentIndex, comboBoxAction.currentIndex, 0, 0, 0);
                    break;
            }
        }

        comboBoxAction.onCurrentIndexChanged: {
            function resetLayout()
            {
                rowLayoutActionLvl.visible = false;
                rowLayoutActionR.visible = false;
                rowLayoutActionG.visible = false;
                rowLayoutActionB.visible = false;
            }

            switch(comboBoxAction.currentIndex)
            {
                case 3:
                    resetLayout();
                    rowLayoutActionLvl.visible = true;
                    break;
                case 13:
                    resetLayout();
                    rowLayoutActionR.visible = true;
                    rowLayoutActionG.visible = true;
                    rowLayoutActionB.visible = true;
                    break;
                default:
                    resetLayout();
                    break;
            }
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
                        tx_model_channels.setProperty(model.index, "text", text)
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
