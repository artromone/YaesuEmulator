import QtQuick 2.0
import QtQuick.Controls 2.0

import YaesuEmulator 1.0

Item {

    implicitHeight: rowId.childrenRect.height
    implicitWidth: rowId.childrenRect.width

        Row
        {
            id: rowId
            spacing: 12

            Text {

                id: antennaState

                font.pointSize: 19
                text: qsTr("Состояние антенны: %1.").arg(widget.antennaStatusString(widget.antennaStatus))
            }

            Text {

                id: antennaCoords

                font.pointSize: 19
                text: qsTr("Положение: [%1;%2], ЦУ: [%3;%4].")
                .arg(widget.az)
                .arg(widget.el)
                .arg(widget.targetAz)
                .arg(widget.targetEl)
            }

            Text {

                id: antennaError

                font.pointSize: 19
                text: "Ошибка."
                visible: false
            }
        }
    }
