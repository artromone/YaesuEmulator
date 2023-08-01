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
            text: qsTr("Состояние антенны: %1").arg(widget.antennaStatusString(widget.antennaStatus))

            //text: AntennaState.S_READY
        }

        Text {

            id: antennaPos

            font.pointSize: 19
            text: qsTr("Положение: %1").arg(widget.antennaCoordsString(widget.antennaCoords))
        }

        Text {

            id: antennaTarget

            font.pointSize: 19
            text: "ЦУ:"
        }

        Text {

            id: antennaError

            font.pointSize: 19
            text: "Ошибка"
        }
    }
}
