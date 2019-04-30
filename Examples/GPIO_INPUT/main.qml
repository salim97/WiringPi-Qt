import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("GPIO INPUT EXAMPLE")
    Item {
        id: name
        anchors.fill: parent
        Button{
            id: button
            anchors.centerIn: parent
            height: 50
            width: 100
            text : myGPIO.button1 == true ? "pressed" : "released"
            enabled: myGPIO.button1
        }

    }
}
