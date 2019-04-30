#ifndef MYGPIO_H
#define MYGPIO_H
#include <QObject>
#include "wiringPi-Qt.h"

class MyGPIO : public QObject
{
    Q_OBJECT

public:
    explicit MyGPIO(QObject *parent = 0);

    CONVERT_CLASS_INTO_SINGELTON(MyGPIO)

    INPUT_GPIO_PROPERTY(button1,     7,  INT_EDGE_BOTH, PUD_DOWN)

};


#endif // MYGPIO_H
