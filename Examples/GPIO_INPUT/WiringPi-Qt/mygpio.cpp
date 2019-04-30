#include "mygpio.h"



MyGPIO* MyGPIO::m_MyGPIO = 0;

MyGPIO::MyGPIO(QObject *parent) : QObject(parent)
{
    CALL_THIS_IN_CONSTRACTEUR_FOR_INPUT_OUTPUT_GPIO

}







