import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml 2.0

Item {

    Connections {

        target: logger

        property string redPrefix: "<span style='color:red'>";
        property string blackPrefix: "<span style='color:black'>";
        property string bluePrefix: "<span style='color:blue'>";

        onLogMessage:
        {
            logArea.append((logType == 1 ? blackPrefix : (logType == 3 ? bluePrefix : blackPrefix))
                           + logMsg + "</span>")
        }
    }

    Text {

        id: logSectionTitle

        font.pointSize: 19
        text: qsTr("Логи: (" + logArea.lineCount + qsTr(")"))
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

            textFormat: TextEdit.RichText
            selectByMouse: true
        }
    }
}
