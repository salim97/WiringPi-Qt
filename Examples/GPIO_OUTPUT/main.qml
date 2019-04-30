import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Item {
        id: name
        anchors.fill: parent
        Row{
            spacing: 50
            anchors.centerIn: parent
            Button{
                height: 50
                width: 100
                text: "blue"
                onClicked: {
                    myGPIO.led_blue = (myGPIO.led_blue +1) % 2
                    console.log(myGPIO.led_blue)
                }
            }

            Button{
                height: 50
                width: 100
                text: "red"
                onClicked: {
                    myGPIO.led_red = (myGPIO.led_red +1) % 2
                    console.log(myGPIO.led_red)

                }
            }





            Button{
                height: 50
                width: 100
                text: "green"
                onClicked: {
                    myGPIO.led_green = (myGPIO.led_green +1) % 2
                    console.log(myGPIO.led_green)
                }
            }

            Button{
                height: 50
                width: 100
                text: "yellow"
                onClicked: {
                    myGPIO.led_yellow = (myGPIO.led_yellow +1) % 2
                    console.log(myGPIO.led_yellow)
                }
            }
        }











    }
}
