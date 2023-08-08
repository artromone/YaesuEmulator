import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml 2.0

Item {

    Connections {

        target: logger

        onLogMessage:
        {
            logArea.append(logMsg)
            // logArea.color = logType == 2 ? "red" : "black"
        }
    }

    Text {

        id: logSectionTitle

        font.pointSize: 19
        text: qsTr("Логи:")
    }

    ScrollView {

        anchors {

            left: parent.left
            right: parent.right
            top: logSectionTitle.bottom
            bottom: parent.bottom
        }

        TextArea {

            id: logArea

            selectByMouse: true
        }
    }
}
