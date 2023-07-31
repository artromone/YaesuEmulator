import QtQuick 2.0
import QtQuick.Controls 2.0

Item {

    Text
    {

        id: logSectionTitle

        font.pointSize: 19
        text: qsTr("Логи:")
    }

//    Rectangle
//    {
//        color: "red"
//        anchors
//                {
//                    left: parent.left
//                    right: parent.right
//                    top: /*logSectionTitle.bottom*/parent.top
//                    bottom: parent.bottom
//                }
//    }

    TextArea
    {
        id: columnId

        clip: true

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
        for (var i=0; i<100; ++i)
        {
            columnId.append(qsTr(i.toString()))
        }
    }
}
