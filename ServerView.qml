import QtQuick 2.0
import QtQuick.Controls 2.0

Item {

    Button {

        id: connectButton

        anchors {
            left: parent.right; leftMargin: leftMargin_
            top: parent.top; topMargin: topMargin_
        }

        width: btnWidth_ //200
        height: btnWidth_ / 4 //50

        font.pointSize: btnWidth_ / 14 //14
        text: backend.serverState
              ? "Остановить сервер"
              : "Запустить сервер"

        //Свободна, выход в точку, ручное управление

        onClicked: {
            backend.serverState = !backend.serverState
        }
    }

    Text {

        id: textServerState

        visible: true
        // font.bold: true

        anchors {
            left: connectButton.right; leftMargin: leftMargin_
            top: parent.bottom; topMargin: connectButton.height / 2
                                           + font.pointSize / 7
        }

        font.pointSize: btnWidth_ / 14 //14
        text: qsTr(backend.serverState
                   ? "Сервер запущен"
                   : "Сервер остановлен")
    }

    Text {

        id: textCurrPort

        visible: true
        // font.bold: true

        anchors {
            left: parent.left; leftMargin: leftMargin_
            top: connectButton.bottom; topMargin: topMargin_ * 2
        }

        font.pointSize: btnWidth_ / 14 //14
        text: qsTr("Порт сервера:")
    }

    TextInput {

        id: portEdit

        inputMask: "0000"

        anchors {
            left: textCurrPort.right; leftMargin: leftMargin_ / 2
            top: connectButton.bottom; topMargin: topMargin_ * 2
        }

        font.pointSize: btnWidth_ / 14 //14
        text: backend.port

        readOnly: backend.serverState
        color: backend.serverState ? "black" : "gray"
    }

//    Text {

//        id: textBusyPort

//        visible: false

//        anchors {
//            left: connectButton.right; leftMargin: 12
//            top: parent.top; topMargin: 12
//        }

//        text: qsTr("Ошибка запуска сервера. Порт занят.")
//    }
}
