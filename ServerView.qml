import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    // property real maxHeight: Math.max()
    implicitHeight: rowId.childrenRect.height
    implicitWidth: rowId.childrenRect.width

    Row
    {
        id: rowId
        spacing: 12

        Text {

            id: textCurrPort
            height: connectButton.height
            verticalAlignment: Text.AlignBottom

            font.pointSize: 19
            text: qsTr("Порт сервера:")
        }

        TextField {

            id: portEdit

            inputMask: "0000"

            width: 90

            font.pointSize: 19

            placeholderText: backend.port
            text: backend.port

            onTextChanged: {
                backend.port = text
            }

            readOnly: backend.serverState
            color: backend.serverState ? "black" : "gray"
        }

        Button {

            id: connectButton

            width: 266

            font.pointSize: 19
            text: backend.serverState
                  ? "Остановить сервер"
                  : "Запустить сервер"

            onClicked: {
                backend.serverState = !backend.serverState
            }
        }

        Text {

            id: textServerState

            font.pointSize: 19

            text: qsTr(backend.serverState
                       ? "Сервер запущен"
                       : backend.serverOK ? "Сервер запущен" : "Ошибка: порт занят")
        }

    }
}
