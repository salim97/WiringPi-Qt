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

    OUTPUT_GPIO_PROPERTY(led_green, 23)
    OUTPUT_GPIO_PROPERTY(led_red, 24)
    OUTPUT_GPIO_PROPERTY(led_blue, 22)
    OUTPUT_GPIO_PROPERTY(led_yellow, 25)

};


#endif // MYGPIO_H
