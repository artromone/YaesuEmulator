import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.1

Window {

    visible: true

    width: 800
    height: 500
    minimumWidth: 550
    minimumHeight: 200

    property var backend: widget

    property int btnWidth_: 266

    property int topMargin_: 16
    property int leftMargin_: 16

    title: qsTr("Yaesu Emulator")

//    Rectangle
//    {
//        id: redRect
//        height: 50
//        width: 50
//        color: "red"
//        anchors
//        {
//            left: parent.left; leftMargin: 12
//            top: parent.top; topMargin: 12
//        }
//    }

//    Rectangle
//    {
//        id: yelRect
//        height: 50
//        width: 50
//        color: "yellow"
//        anchors
//        {
//            left: redRect.right;
//            top: parent.top; topMargin: 12
//        }
//    }

//    Rectangle
//    {
//        id: grRect
//        height: 50
//        width: 50
//        color: "green"
//        anchors
//        {
//            left: parent.left; leftMargin: 12
//            top: redRect.bottom;
//        }
//    }

//    Rectangle
//    {
//        id: blRect
//        height: 50
//        width: 50
//        color: "blue"
//        anchors
//        {
//            left: grRect.right;
//            top: yelRect.bottom;
//        }
//    }

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
        anchors
        {
            left: parent.left
            top: serverViewLayout.bottom
        }
    }
}
