import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.1

Window {
    visible: true
    minimumWidth: 300
    minimumHeight: 100
    width: 800
    height: 500
    title: qsTr("Yaesu Emulator")


    Rectangle {

        anchors.centerIn: parent
        width: 50
        height: 50
        color: rectColor
    }

    TextInput {

        id: portEdit

        anchors {
            left: parent.left; leftMargin: 12
            top: parent.top; rightMargin: 12
        }
        width: 250
        text: widget.port
    }

}
