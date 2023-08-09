import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.1

Window
{
    property var backend: widget
    readonly property int btnWidth_: 260
    readonly property int topMargin_: 16
    readonly property int leftMargin_: 16

    visible: true
    width: 650
    height: 280
    minimumWidth: 650
    minimumHeight: 280
    title: qsTr("Yaesu Emulator")

    ServerView
    {
        id: serverViewLayout

        height: 170
        width: 300

        anchors
        {
            left: parent.left;
            bottomMargin: 0;
            margins: 12;
            top: parent.top
        }
    }

    EmulatorView
    {
        id: emulatorViewLayout

        height: 100
        width: 300

        anchors
        {
            left: parent.left;
            bottomMargin: 0;
            margins: 12;
            top: serverViewLayout.bottom;
            topMargin: topMargin_
        }
    }

    LoggerView
    {
        id: loggerViewLayout

        anchors
        {
            left: serverViewLayout.right
            right: parent.right
            bottomMargin: 0;
            margins: 12;
            top: parent.top;
            topMargin: topMargin_
            bottom: parent.bottom
        }
    }
}
