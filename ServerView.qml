import QtQuick 2.0
import QtQuick.Controls 2.0

import YaesuEmulator 1.0

Item {

    property bool serverConnected: (backend.serverState === ServerState.S_CONNECTED)

    // property real maxHeight: Math.max()
    implicitHeight: rowId.childrenRect.height
    implicitWidth: rowId.childrenRect.width

    Row {

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
            enabled: !serverConnected
            color: serverConnected ? "black" : "gray"

            onTextChanged: backend.port = text
        }

        Button {

            id: connectButton

            width: 266
            font.pointSize: 19
            text: serverConnected ? qsTr("Остановить сервер") : qsTr("Запустить сервер")

            onClicked: backend.changeServerState(!serverConnected)
        }

        Text {

            id: textServerState

            font.pointSize: 19
            height: connectButton.height
            verticalAlignment: Text.AlignBottom
            text: serverConnected ? qsTr("Сервер запущен")
                                  : backend.serverState === ServerState.S_PORT_BUSY ? qsTr("Ошибка: порт занят")
                                                                                    : qsTr("Сервер остановлен")
        }
    }
}
