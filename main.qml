import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: nooliteToolRX
    title: qsTr("RX Tool")
    width: 840
    height: 480
    minimumWidth: 840
    minimumHeight: 480
    visible: true

    property int lang_english : 1
    property int lang_russian : 2
    property int lang_ukrainian : 3

    MainForm {
        id: mainForm
        anchors.fill: parent

        settingsButton.onClicked: messageDialog.show(qsTr("This functionality not Implemented!"));
        exitButton.onClicked: Qt.quit();
        openScriptButton.onClicked: fileDialog.open()

        listViewConsoles.delegate: Item {
            property var view: ListView.view
            property var isCurrent: ListView.isCurrentItem

            width: view.width
            height: 40

            Rectangle {
                anchors.margins: 5
                anchors.fill: parent                
                border {
                    color: "black"
                    width: 1
                }

                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: view.currentIndex = model.index
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

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
