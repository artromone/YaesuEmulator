import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.1

Window {

    property var backend: widget

    visible: true

    minimumWidth: 300
    minimumHeight: 100
    width: 800
    height: 500

    title: qsTr("Yaesu Emulator")

    ServerView {

        anchors {

            left: parent.left
            top: parent.top
        }
    }
}
