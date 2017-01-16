import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4

Item {
    id: rxTool
    width: cpp_controller.rxWidth
    height: cpp_controller.rxHeight

    property alias listViewConsoles: listViewConsoles
    property alias exitButton: exitButton
    property alias settingsButton: settingsButton
    property alias openScriptButton: openScriptButton
    property alias textFieldScriptPath : textFieldScriptPath
    property alias buttonBind: buttonBind
    property alias buttonUnbind: buttonUnbind
    property alias buttonSave: buttonSave
    property alias comboBoxAction: comboBoxAction
    property alias modelActions: modelActions
    property alias switchForwardData: switchForwardData
    property alias switchForwardExtData: switchForwardExtData

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

            model: rx_model_channels//cpp model
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
        checked: rx_model_status.active
        anchors.left: parent.left
        anchors.leftMargin: 8
        title: qsTr("Status:")

        onCheckedChanged: rx_model_status.active = checked

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
            anchors.leftMargin: 240
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            RowLayout {
                id: rowLayoutData1
                width: 143
                height: 20
                Label {
                    id: labelData1Text
                    text: qsTr("Data[1]:")
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelData1
                    text: rx_model_status.data1
                    font.family: "Times New Roman"
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
                    id: labelData3Text
                    text: qsTr("Data[3]:")
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelData3
                    text: rx_model_status.data3
                    font.family: "Times New Roman"
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
                    id: labelData0Text
                    text: qsTr("Data[0]:")
                    verticalAlignment: Text.AlignBottom
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelData0
                    text: rx_model_status.data0
                    font.family: "Times New Roman"
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
                    id: labelData2Text
                    text: qsTr("Data[2]:")
                    verticalAlignment: Text.AlignBottom
                    font.pointSize: 14
                    font.family: "Times New Roman"
                    font.bold: false
                    Layout.fillHeight: true
                }

                Label {
                    id: labelData2
                    text: rx_model_status.data2
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
                    id: labelTogl
                    text: "[" + rx_model_status.togl + "]"
                    verticalAlignment: Text.AlignBottom
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    Layout.fillHeight: true
                    font.family: "Times New Roman"
                    font.pointSize: 14
                    font.bold: false
                }

                Label {
                    id: labelActopText
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
                    id: labelAction
                    text: rx_model_status.action
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
                    text: rx_model_status.channel
                    font.family: "Times New Roman"
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
            id: comboBoxAction
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            model: ListModel {
                id: modelActions
                ListElement { text: qsTr("Turn off");   }
                ListElement { text: qsTr("Slow turn off");    }
                ListElement { text: qsTr("Turn on");  }
                ListElement { text: qsTr("Slow turn on");  }
                ListElement { text: qsTr("Switch");  }
                ListElement { text: qsTr("Revert slow turn");  }
                ListElement { text: qsTr("Set level");  }
                ListElement { text: qsTr("Run scene");  }
                ListElement { text: qsTr("Record scene");  }
                ListElement { text: qsTr("Unbind");  }
                ListElement { text: qsTr("Stop dim bright");  }
                ListElement { text: qsTr("Bind");  }
                ListElement { text: qsTr("Slow RGB change");  }
                ListElement { text: qsTr("Switch color");  }
                ListElement { text: qsTr("Switch mode");  }
                ListElement { text: qsTr("Switch speed mode");  }
                ListElement { text: qsTr("Battery low");  }
                ListElement { text: qsTr("Temperature");  }
            }
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
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        RowLayout {
            id: rowLayout1
            height: 100
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            TextField {
                id: textFieldScriptPath
                placeholderText: "\\home\\user\\path_example\\rx-action.sh"
                text: rx_model_channel_cfg.script
                anchors.topMargin: 8
                anchors.right: openScriptButton.left
                anchors.rightMargin: 4
                anchors.left: parent.left
                anchors.leftMargin: 0
            }

            ToolButton {
                id: openScriptButton
                text: "..."
                anchors.right: parent.right
                anchors.rightMargin: 0
            }
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
            id: buttonBind

            width: 110
            text: qsTr("Bind")

            Layout.fillHeight: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            Layout.fillWidth: true
        }
        Button {
            id: buttonUnbind
            width: 110
            text: qsTr("Unbind")
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
                checked: rx_model_channel_cfg.fw
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
                id: switchForwardExtData
                width: 300
                height: 25
                antialiasing: false
                Layout.fillWidth: false
                checked: rx_model_channel_cfg.fwExt
            }

            Label {
                id: labelExtData
                text: qsTr("Add extended data to script arguments")
                anchors.left: switchForwardExtData.right
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
        text: qsTr("Channels:")
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

