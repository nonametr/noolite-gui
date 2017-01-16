import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {

    id: nooliteToolSettingsRX
    title: qsTr("RX Tool settings")
    visible: true
    flags: Qt.SubWindow
    modality: Qt.ApplicationModal
    width: 400
    height: 150
    minimumWidth: 400
    minimumHeight: 150

    RxToolSettingsWindow {
        id: rxToolSettings
        anchors.fill: parent

        openScriptButton.onClicked: fileDialog.open()
        exitButton.onClicked: close()
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
            rxToolSettings.textFieldScriptPath.text = path
        }
        onRejected: {
            console.log("File selection canceled")
        }
    }
}
