import QtQuick 2.0
import QtQuick.Controls 2.0

import YaesuEmulator 1.0

Item {

    readonly property bool serverConnected: (backend.serverState === ServerState.S_CONNECTED)

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

        CheckBox
        {
            id: autoConnect

            checked: backend.autoConnect
            text: qsTr("Автоподключение")
            height: connectButton.height

            onClicked: backend.changeAutoconectOption(autoConnect.checked)
        }
    }
}
