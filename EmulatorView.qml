import QtQuick 2.0
import QtQuick.Controls 2.0

import YaesuEmulator 1.0

Item
{
    implicitHeight: rowId.childrenRect.height
    implicitWidth: rowId.childrenRect.width

        Text
        {
            id: antennaState

            font.pointSize: 19
            text: qsTr("Антенна: %1.").arg(widget.antennaStatusString(widget.antennaStatus))

            anchors.top: parent.top
            anchors.left: parent.left
        }

        Text
        {
            id: antennaCoords

            font.pointSize: 19
            text: qsTr("ПЗ: [%1;%2], ЦУ: [%3;%4].")
            .arg(widget.az)
            .arg(widget.el)
            .arg(widget.targetAz)
            .arg(widget.targetEl)

            anchors.top: antennaState.bottom
            anchors.left: parent.left
        }

//            Text
//            {
//                id: antennaError

//                font.pointSize: 19
//                text: "Ошибка."
//                visible: false

//                anchors.top: antennaState.top
//                anchors.left: parent.left
//            }

        }

