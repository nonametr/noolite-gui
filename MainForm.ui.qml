import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: mainForm
    width: 840
    height: 480

    property alias listViewConsoles: listViewConsoles
    property alias modelConsoles: modelConsoles

    ListModel {
        id: modelConsoles

        ListElement {
            text: "channel 1"
        }
        ListElement {
            text: "channel 2"
        }
        ListElement {
            text: "channel 3"
        }
        ListElement {
            text: "channel 4"
        }
        ListElement {
            text: "channel 5"
        }
        ListElement {
            text: "channel 6"
        }
        ListElement {
            text: "channel 7"
        }
        ListElement {
            text: "channel 8"
        }
        ListElement {
            text: "channel 9"
        }
        ListElement {
            text: "channel 10"
        }
        ListElement {
            text: "channel 11"
        }
    }

    Rectangle {
        id: rectConsoles
        width: 250
        border.color: "black"
        anchors.bottom: statusBox.top
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

            model: modelConsoles
            clip: true

            highlight: Rectangle {
                color: "skyblue"
            }

            highlightFollowsCurrentItem: true
        }
    }

    GroupBox {
        id: statusBox
        height: 100
        anchors.right: columnLayoutExit.left
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        checkable: true
        flat: false
        checked: true
        anchors.left: parent.left
        anchors.leftMargin: 8
        title: qsTr("Status:")

        GridLayout {
            id: gridLayout1
            x: 175
            y: 14
            width: 169
            height: 56
            columnSpacing: 8
            rowSpacing: 8
            rows: 2
            columns: 2
            anchors.left: columnLayout1.right
            anchors.leftMargin: 32
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            RowLayout {
                id: rowLayoutData1
                width: 143
                height: 20
                Label {
                    id: labelChannelText3
                    text: qsTr("Data[1]:")
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelChannel3
                    text: qsTr("2")
                    font.pointSize: 14
                    font.bold: false
                    Layout.fillHeight: true
                }
            }

            RowLayout {
                id: rowLayoutData3
                width: 143
                height: 20
                Label {
                    id: labelChannelText5
                    text: qsTr("Data[3]:")
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelChannel5
                    text: qsTr("4")
                    font.pointSize: 14
                    font.bold: false
                    Layout.fillHeight: true
                }
            }

            RowLayout {
                id: rowLayoutData0
                width: 143
                height: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                Label {
                    id: labelChannelText2
                    text: qsTr("Data[0]:")
                    verticalAlignment: Text.AlignBottom
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelChannel2
                    text: qsTr("1")
                    verticalAlignment: Text.AlignBottom
                    font.pointSize: 14
                    font.bold: false
                    Layout.fillHeight: true
                }
            }

            RowLayout {
                id: rowLayoutData2
                width: 143
                height: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                Label {
                    id: labelChannelText4
                    text: qsTr("Data[2]:")
                    verticalAlignment: Text.AlignBottom
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelChannel4
                    text: qsTr("3")
                    verticalAlignment: Text.AlignBottom
                    font.family: "Times New Roman"
                    font.pointSize: 14
                    font.bold: false
                    Layout.fillHeight: true
                }
            }
        }

        ColumnLayout {
            id: columnLayout1
            y: 0
            width: 100
            height: 56
            spacing: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 8

            RowLayout {
                id: rowLayoutAction
                width: 143
                height: 25
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                Label {
                    id: labelChannelText1
                    text: qsTr("Action:")
                    verticalAlignment: Text.AlignBottom
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    Layout.fillHeight: true
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                }

                Label {
                    id: labelChannel1
                    text: qsTr("Switch[4]")
                    verticalAlignment: Text.AlignBottom
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    Layout.fillHeight: true
                    font.family: "Times New Roman"
                    font.pointSize: 14
                    font.bold: false
                }
            }

            RowLayout {
                id: rowLayoutChannel
                width: 143
                height: 22
                Layout.fillWidth: true
                anchors.bottom: rowLayoutAction.top
                anchors.bottomMargin: 8

                Label {
                    id: labelChannelText
                    text: qsTr("Channel:")
                    Layout.fillHeight: true
                    font.bold: false
                    font.pointSize: 14
                    font.family: "Times New Roman"
                }

                Label {
                    id: labelChannel
                    text: qsTr("14")
                    Layout.fillHeight: true
                    font.bold: false
                    font.pointSize: 14
                }
            }
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
            id: comboBox1
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
        }
    }

    ColumnLayout {
        id: columnLayoutScript
        y: 66
        height: 43
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: rectConsoles.right
        anchors.leftMargin: 8
        Label {
            id: actionLabel1
            text: qsTr("Script")
        }

        TextField {
            id: textFieldScriptPath
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            placeholderText: qsTr("Text Field")
        }
    }

    RowLayout {
        id: rowLayoutLink
        y: 235
        height: 37
        anchors.bottom: rectConsoles.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: rectConsoles.right
        anchors.leftMargin: 8
        spacing: 0




        Button {
            id: buttonLink
            width: 110
            text: qsTr("Link")
            Layout.fillHeight: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            Layout.fillWidth: true
        }
        Button {
            id: buttonClean
            width: 110
            text: qsTr("Clean")
            Layout.fillHeight: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            Layout.fillWidth: true
        }
        Button {
            id: buttonSave
            width: 110
            text: qsTr("Save")
            Layout.fillHeight: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            Layout.fillWidth: true
        }
    }

    ColumnLayout {
        id: columnLayoutFlags
        height: 48
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: rectConsoles.right
        anchors.leftMargin: 8
        anchors.top: columnLayoutScript.bottom
        anchors.topMargin: 8

        RowLayout {
            id: rowLayoutSwitchForwardData
            width: 100
            height: 100
            spacing: 3

            Switch {
                id: switchForwardData
                width: 300
                height: 25
                Layout.fillWidth: false
            }

            Label {
                id: labelForwardData
                text: qsTr("Forward input data as script arguments")
                anchors.left: switchForwardData.right
                anchors.leftMargin: 8
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: false
            }
        }

        RowLayout {
            id: rowLayoutSwitchExtData
            width: 100
            height: 100
            Switch {
                id: switchExtData
                width: 300
                height: 25
                Layout.fillWidth: false
            }

            Label {
                id: labelExtData
                text: qsTr("Add extended data to script arguments")
                anchors.left: switchExtData.right
                anchors.leftMargin: 8
                Layout.fillWidth: false
            }
            spacing: 3
        }
    }

Label {
    id: labelConsoles
    x: 8
    y: 8
    text: qsTr("Consoles:")
    anchors.left: parent.left
    anchors.leftMargin: 8
    anchors.top: parent.top
    anchors.topMargin: 8
}

ColumnLayout {
    id: columnLayoutExit
        anchors.left: rowLayoutLink.horizontalCenter
        anchors.leftMargin: 8
        anchors.top: rowLayoutLink.bottom
        anchors.topMargin: 8
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
            id: settingsButton
            height: 50
            text: qsTr("Settings")
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

