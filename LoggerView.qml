import QtQuick 2.0
import QtQuick.Controls 2.0

Item {

    Text
    {
        id: logSectionTitle

        font.pointSize: 19
        text: qsTr("Логи:")
    }

    TextArea
    {
        id: logArea

        clip: true
        selectByMouse: true

        anchors
        {
            left: parent.left
            right: parent.right
            top: logSectionTitle.bottom
            bottom: parent.bottom
        }
    }

    Component.onCompleted:
    {
        var time = backend.logMsg
        logArea.append(qsTr(time + ":"))
    }
}
