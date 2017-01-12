import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4

Item {
    id: txTool
    width: 500
    height: 400

    property alias lvlSpinBox: lvlSpinBox
    property alias rSpinBox: rSpinBox
    property alias gSpinBox: gSpinBox
    property alias bSpinBox: bSpinBox
    property alias buttonExecute: buttonExecute
    property alias listViewConsoles: listViewConsoles
    property alias comboBoxAction: comboBoxAction
    property alias rowLayoutActionLvl: rowLayoutActionLvl
    property alias rowLayoutActionR: rowLayoutActionR
    property alias rowLayoutActionG: rowLayoutActionG
    property alias rowLayoutActionB: rowLayoutActionB

    Label {
        id: labelConsoles
        x: 8
        y: 8
        text: qsTr("Channels:")
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
    }

    Rectangle {
        id: rectConsoles
        width: 250
        border.color: "black"
        anchors.bottom: rowLayoutExecute.top
        anchors.bottomMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: labelConsoles.bottom
        anchors.topMargin: 8

        ListView {
            id: listViewConsoles
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.rightMargin: 8
            anchors.leftMargin: 8
            anchors.bottomMargin: 8
            anchors.topMargin: 8

            boundsBehavior: Flickable.StopAtBounds

            model: tx_model_channels //cpp model
            clip: true

            highlight: Rectangle {
                color: "skyblue"
            }

            highlightFollowsCurrentItem: true
        }
    }

    ColumnLayout {
        id: columnLayoutAction
        y: 8
        height: 43
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: rectConsoles.right
        anchors.leftMargin: 8

        Label {
            id: actionLabel
            text: qsTr("Action")
        }

        ComboBox {
            id: comboBoxAction
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            model: ListModel {
                id: modelActions
                ListElement {
                    text: qsTr("On")
                }
                ListElement {
                    text: qsTr("Off")
                }
                ListElement {
                    text: qsTr("Switch")
                }
                ListElement {
                    text: qsTr("Set level")
                }
                ListElement {
                    text: qsTr("Bind")
                }
                ListElement {
                    text: qsTr("Unbind")
                }
                ListElement {
                    text: qsTr("Load preset")
                }
                ListElement {
                    text: qsTr("Save preset")
                }
                ListElement {
                    text: qsTr("Stop change")
                }
                ListElement {
                    text: qsTr("Roll color")
                }
                ListElement {
                    text: qsTr("Switch color")
                }
                ListElement {
                    text: qsTr("Switch mode")
                }
                ListElement {
                    text: qsTr("Switch speed change color")
                }
                ListElement {
                    text: qsTr("Set color")
                }
            }
        }
    }

    RowLayout {
        id: rowLayoutExecute
        y: 235
        height: 37
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        spacing: 0

        Button {
            id: buttonExecute

            width: 110
            text: qsTr("Execute")

            Layout.fillHeight: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            Layout.fillWidth: true
        }
    }

    ColumnLayout {
        id: columnLayoutActionData
        height: 43
        anchors.top: columnLayoutAction.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: rectConsoles.right
        anchors.leftMargin: 8

        RowLayout {
            id: rowLayoutActionLvl
            visible: false

            Label {
                id: lvlLabel
                width: 100
                text: qsTr("Level:")
                Layout.fillWidth: true
            }

            SpinBox {
                id: lvlSpinBox
                decimals: 2
            }
        }

        RowLayout {
            id: rowLayoutActionR
            visible: false

            Label {
                id: rLabel
                width: 100
                text: qsTr("Red:")
                Layout.fillWidth: true
            }

            SpinBox {
                id: rSpinBox
                decimals: 2
            }
        }

        RowLayout {
            id: rowLayoutActionG
            visible: false

            Label {
                id: gLabel
                width: 100
                text: qsTr("Green:")
                Layout.fillWidth: true
            }

            SpinBox {
                id: gSpinBox
                decimals: 2
            }
        }

        RowLayout {
            id: rowLayoutActionB
            visible: false

            Label {
                id: bLabel
                width: 100
                text: qsTr("Blue:")
                Layout.fillWidth: true
            }

            SpinBox {
                id: bSpinBox
                decimals: 2
            }
        }
    }
}
