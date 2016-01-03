import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: nooliteToolRX
    title: qsTr("RX Tool")
    width: 900
    height: 480
    minimumWidth: 900
    minimumHeight: 480
    visible: true

    property int lang_english : 1
    property int lang_russian : 2
    property int lang_ukrainian : 3

    ListModel {
           id: modelConsoles2

           ListElement {
               text: "channel #1"
           }
           ListElement {
               text: "second"
           }
           ListElement {
               text: "third"
           }
           ListElement {
               text: "fourth"
           }
       }

    MainForm {
        id: mainForm
        anchors.fill: parent

        settingsButton.onClicked: messageDialog.show(qsTr("This functionality not Implemented!"));
        exitButton.onClicked: Qt.quit();
        openScriptButton.onClicked: fileDialog.open()

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
                        modelConsoles.setProperty(model.index, "text", text)
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
                        if(mouse.button == Qt.LeftButton)
                        {
                            parent.forceActiveFocus(Qt.MouseFocusReason)
                            view.currentIndex = model.index
                            console.log(model.channel)
                            for(var i = 0; i < model.act_ount; ++i) {
                                console.log(model.getAction(i).action_name);
                            }
                        }
                        else if(mouse.button == Qt.RightButton) {
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
