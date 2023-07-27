import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.1

Window {
    visible: true

    minimumWidth: 300
    minimumHeight: 100
    width: 800
    height: 500

    title: qsTr("Yaesu Emulator")

    TextInput {

        id: portEdit

//        inputMask: "0000"

        anchors {
            left: parent.left; leftMargin: 50
            top: parent.top; topMargin: 12
        }

        width: 250

        text: widget.port
    }

    Button {

        id: connectButton

        anchors {
            left: portEdit.right; leftMargin: 12
            top: parent.top; topMargin: 12
        }

        //text: qsTr("Запустить сервер")

        text: widget.serverState ? "остановить" : "запустить"

        //Свободна, выход в точку, ручное управление

        onClicked: {
            console.log(widget.serverState)
            widget.serverState = !widget.serverState
        }
    }
}
