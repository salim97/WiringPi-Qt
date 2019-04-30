# WiringPi for Qt

WiringPi: An implementation of most of the Arduino Wiring functions for the Raspberry Pi.

WiringPi-Qt : Adding Qt Signals &amp; Slots to WiringPi.

# Setup
1) copy WiringPi-Qt folder to your project
2) go to .pro file of your project and add at the end those lines

```
INCLUDEPATH += $$PWD/WiringPi-Qt
include(WiringPi-Qt/WiringPi-Qt.pri)
```

# Examples

https://github.com/salim97/WiringPi-Qt/tree/master/Examples
```
#include <QObject>
#include "wiringPi-Qt.h"

class MyGPIO : public QObject
{
    Q_OBJECT

public:
    explicit MyGPIO(QObject *parent = 0);

    CONVERT_CLASS_INTO_SINGELTON(MyGPIO)

    INPUT_GPIO_PROPERTY(button1,     7,  INT_EDGE_BOTH, PUD_DOWN)
    
    OUTPUT_GPIO_PROPERTY(led_green, 23)

};
```

# Usage
open terminal and run 
```
$ gpio readall
```
wPInumberPIN represent wPi number in the table

## OUTPUT_GPIO_PROPERTY(NAME, wPInumberPIN)
to specifie pin as an output

## INPUT_GPIO_PROPERTY(NAME, wPInumberPIN, INT_MODE, PUD_MODE)
to specifie pin as an input
INT_MODE : INT_EDGE_FALLING, INT_EDGE_RISING, INT_EDGE_BOTH, INT_EDGE_SETUP .
PUD_MODE: PUD_UP, PUD_DOWN, PUD_OFF

check this site for more information :
http://wiringpi.com/reference/priority-interrupts-and-threads/



# Details about requirement in order to work proprely
## header
1) the class must inherite from QObject and contain the Q_OBJECT macro in it
2) add CONVERT_CLASS_INTO_SINGELTON() macro in order to be singelton, and class name in paramter 
3) use INPUT_GPIO_PROPERTY and OUTPUT_GPIO_PROPERTY as much as you can

```
#include <QObject>
#include "wiringPi-Qt.h"

class MyGPIO : public QObject
{
    Q_OBJECT

public:
    explicit MyGPIO(QObject *parent = 0);

    CONVERT_CLASS_INTO_SINGELTON(MyGPIO)

    INPUT_GPIO_PROPERTY(button1,     7,  INT_EDGE_BOTH, PUD_DOWN)
    
    OUTPUT_GPIO_PROPERTY(led_green, 23)

};
```
## source
1) add this above contrecteur 
```
MyGPIO* MyGPIO::m_MyGPIO = 0;
```
2) add CALL_THIS_IN_CONSTRACTEUR_FOR_INPUT_OUTPUT_GPIO in contrecteur
```
MyGPIO* MyGPIO::m_MyGPIO = 0;

MyGPIO::MyGPIO(QObject *parent) : QObject(parent)
{
    CALL_THIS_IN_CONSTRACTEUR_FOR_INPUT_OUTPUT_GPIO

}
```
