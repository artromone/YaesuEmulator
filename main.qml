import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.1

Window {

    visible: true

    property double scale: 2

    width: 800 * scale //800
    height: width / 1.6 //500
    minimumWidth: width / 1.45 //550
    minimumHeight: height / 5 //100

    property var backend: widget

    property int btnWidth_: width / 4 //200

    property int topMargin_: btnWidth_ / 16 //12
    property int leftMargin_: btnWidth_ / 16 //12

    title: qsTr("Yaesu Emulator")

    ServerView {

        anchors {

            left: parent.left
            top: parent.top
        }
    }
}
