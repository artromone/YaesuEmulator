import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

import YaesuEmulator 1.0

Item {

    readonly property bool serverConnected: (backend.serverState === ServerState.S_CONNECTED)

    // property real maxHeight: Math.max()
    implicitHeight: rowId.childrenRect.height
    implicitWidth: rowId.childrenRect.width

    Text
    {
        id: textCurrPort

        height: connectButton.height
        verticalAlignment: Text.AlignBottom
        font.pointSize: 19
        text: qsTr("Порт сервера:")

        anchors.top: parent.top
        anchors.left: parent.left
    }

    TextField
    {
        id: portEdit

        inputMask: "0000"
        width: 90
        font.pointSize: 19
        placeholderText: backend.port
        text: backend.port
        enabled: !serverConnected
        color: serverConnected ? "black" : "gray"

        anchors.top: parent.top
        anchors.left: textCurrPort.right;anchors.leftMargin: 10

        onTextChanged: backend.port = text
    }

    Button {

        id: connectButton
        property color backgroundDefaultColor: "#0ACF97"
        property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)
        property color contentItemTextColor: "white"

        anchors.top: textCurrPort.bottom; anchors.topMargin: 20
        anchors.left: parent.left

        text: serverConnected ? qsTr("Остановить сервер") : qsTr("Запустить сервер")
        contentItem: Text {
            text: connectButton.text
            color: connectButton.contentItemTextColor
            font.pixelSize: 19
            font.family: "Calibri"
            font.weight: Font.Thin
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 266
            implicitHeight: 37
            color: connectButton.down ?
                       connectButton.backgroundPressedColor :
                       connectButton.backgroundDefaultColor
            radius: 5
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                color: connectButton.down ?
                           connectButton.backgroundPressedColor :
                           connectButton.backgroundDefaultColor
                samples: 20
            }
        }

        onClicked: backend.changeServerState(!serverConnected)
    }

    CheckBox
    {
        id: autoConnect

        text: qsTr("Автоподключение")
        checked: backend.autoConnect

        anchors.top: connectButton.bottom; anchors.topMargin: 10
        anchors.left: parent.left

        onClicked: backend.changeAutoconectOption(autoConnect.checked)
    }

    CheckBox
    {
        id: lockTunnel
        text: qsTr("Блокировать связь")
        onClicked: backend.setTunnelLocked(lockTunnel.checked);

        anchors.top: autoConnect.bottom
        anchors.left: parent.left
    }

}
