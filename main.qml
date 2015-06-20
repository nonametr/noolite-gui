import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: nooliteToolRX
    title: qsTr("RX Tool")
    width: 640
    height: 480
    visible: true
/*
    ListModel {
        id: modelConsoles
        ListElement {
            text: "channel 10"
        }
        ListElement {
            text: "channel 11"
        }
    }
*/
    MainForm {
        id: main_form
        anchors.fill: parent  
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

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
