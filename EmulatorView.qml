import QtQuick 2.0
import QtQuick.Controls 2.0

import YaesuEmulator 1.0

Item {

    implicitHeight: rowId.childrenRect.height
    implicitWidth: rowId.childrenRect.width

    Connections {

        target: widget

        onAntennaCoordsChanged: antennaCoords.text =
                                qsTr("Положение: [%1;%2], ЦУ: [%3;%4].").arg(azCurr).arg(elCurr).arg(azTarget).arg(elTarget)
    }

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
        }

        Text {

            id: antennaError

            font.pointSize: 19
            text: "Ошибка."
            visible: false
        }
    }
}
