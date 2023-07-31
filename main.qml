import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.1

Window {

    visible: true

    width: 850
    height: 500
    minimumWidth: 550
    minimumHeight: 200

    property var backend: widget

    property int btnWidth_: 266

    property int topMargin_: 16
    property int leftMargin_: 16

    title: qsTr("Yaesu Emulator")

    ServerView
    {
        id: serverViewLayout
        anchors
        {
            left: parent.left
            top: parent.top
        }
    }

    EmulatorView
    {
        id: emulatorViewLayout
        anchors
        {
            left: parent.left
            top: serverViewLayout.bottom; topMargin: topMargin_
        }
    }

    LoggerView
    {
        id: loggerViewLayout
        anchors
        {
            left: parent.left
            right: parent.right
            top: emulatorViewLayout.bottom; topMargin: topMargin_
            bottom: parent.bottom
        }
    }
}
