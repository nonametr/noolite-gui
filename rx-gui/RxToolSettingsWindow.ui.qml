import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4

Item {
    id: rxToolSettings

    width: 400
    height: 150

    property alias exitButton: exitButton
    property alias openScriptButton: openScriptButton
    property alias textFieldScriptPath: textFieldScriptPath

    ColumnLayout {
        id: columnLayoutScript
        height: 43
        transformOrigin: Item.Center
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8

        RowLayout {
            id: rowLayout1
            x: 0
            width: 400
            height: 100
            clip: false
            opacity: 1
            transformOrigin: Item.Center
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillHeight: false
            Layout.fillWidth: true
            spacing: 8

            Label {
                id: actionLabel1
                width: 100
                text: qsTr("Default script:")
                Layout.preferredWidth: 100
                Layout.fillWidth: false
            }
            TextField {
                id: textFieldScriptPath
                x: 100
                width: 250
                placeholderText: "\\path_example\\rx-action.sh"
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.preferredWidth: -1
                transformOrigin: Item.Center
                Layout.fillHeight: false
            }
            ToolButton {
                id: openScriptButton
                text: "..."
                Layout.fillWidth: false
            }
        }

        RowLayout {
            id: rowLayout2
            x: 0
            y: 30
            width: 400
            height: 100
            clip: false
            spacing: 5
            Layout.rowSpan: 1
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Label {
                id: actionLabel2
                width: 100
                text: qsTr("Default tool:")
                Layout.preferredWidth: 102
                Layout.fillHeight: false
                elide: Text.ElideNone
                verticalAlignment: Text.AlignTop
                Layout.fillWidth: false
            }

            ComboBox {
                id: comboBoxTools
                x: 0
                width: 200
                Layout.rowSpan: 1
                Layout.fillWidth: true

                model: ListModel {
                    id: modelTools
                    ListElement {
                        text: qsTr("Rx Tool")
                    }
                    ListElement {
                        text: qsTr("Tx Tool")
                    }
                }
            }
        }
    }

    ColumnLayout {
        id: columnLayoutExit
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8

        Button {
            id: exitButton
            height: 50
            text: qsTr("Exit")
            Layout.fillHeight: true
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }

        Button {
            id: saveButton
            height: 50
            text: qsTr("Save")
            Layout.fillHeight: true
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }
    }
}
