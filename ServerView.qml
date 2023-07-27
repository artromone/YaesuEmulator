import QtQuick 2.0
import QtQuick.Controls 2.0

Item {

    TextInput {

        id: portEdit

        inputMask: "0000"

        anchors {
            left: parent.left; leftMargin: 30
            top: parent.top; topMargin: 12
        }

        width: 250

        text: backend.port
    }

    Button {

        id: connectButton

        anchors {
            left: portEdit.right; leftMargin: 12
            top: parent.top; topMargin: 12
        }

        width: 160

        text: widget.serverState
              ? "Остановить сервер"
              : "Запустить сервер"

        //Свободна, выход в точку, ручное управление

        onClicked: {
            widget.serverState = !widget.serverState
        }
    }

    Text {

        id: textBusyPort

        visible: false

        anchors {
            left: connectButton.right; leftMargin: 12
            top: parent.top; topMargin: 12
        }

        text: qsTr("Ошибка запуска сервера. Порт занят.")
    }
}
