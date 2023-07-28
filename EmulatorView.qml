import QtQuick 2.0
import QtQuick.Controls 2.0

Item {

    Text {

        id: fgfgfg

        visible: true

        font.pointSize: 19

        text: "Сервер остановлен"

        anchors {
            left: connectButton.right; leftMargin: leftMargin_
            top: parent.bottom; topMargin: connectButton.height / 2
                                           + font.pointSize / 7
        }
    }
}
