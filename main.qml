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

                TextInput {
                    id: textinput
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        textinput.forceActiveFocus()
                        view.currentIndex = model.index
                    }
                }

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
