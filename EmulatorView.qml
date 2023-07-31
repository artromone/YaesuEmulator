import QtQuick 2.0
import QtQuick.Controls 2.0

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
            text: "Состояние антены"
        }

        Text {

            id: antennaPos

            font.pointSize: 19
            text: "Положение:"
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
