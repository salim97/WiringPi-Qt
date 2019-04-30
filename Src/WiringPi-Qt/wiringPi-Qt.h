//#ifndef MYPROPERTYHELPER_H
//#define MYPROPERTYHELPER_H

#pragma once
#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QtCore>
#include "wiringPi.h"

#define DEBUG_MODE true

#define STRINGIFY(x) #x

#define PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
       TYPE NAME() const { return m_ ## NAME ; } \
       void NAME(TYPE value) { \
          if (m_ ## NAME == value)  return; \
          m_ ## NAME = value; \
          emit NAME ## Changed(value); \
        } \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE m_ ## NAME;

#define READONLY_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME CONSTANT ) \
    public: \
       TYPE NAME() const { return m_ ## NAME ; } \
    private: \
       void NAME(TYPE value) {m_ ## NAME = value; } \
       TYPE m_ ## NAME;

#define PROPERTY_SETTINGS(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
        Q_INVOKABLE void _init ## NAME() \
        {\
            QString func_name = Q_FUNC_INFO;\
            func_name = func_name.split("(")[0];\
            func_name = func_name.split("::")[1];\
            func_name.remove(0, 4 );\
            QSettings settings("myapp.ini", QSettings ::IniFormat );\
            m_ ## NAME = qvariant_cast<TYPE>(settings.value(func_name));     \
        }\
       TYPE NAME() const { return m_ ## NAME ; } \
       void NAME(TYPE value) { \
          if (m_ ## NAME == value)  return; \
          QString func_name = Q_FUNC_INFO;\
          func_name = func_name.split("(")[0];\
          func_name = func_name.split("::")[1];\
          QSettings settings("myapp.ini", QSettings ::IniFormat );\
          settings.setValue(func_name , value  );\
          m_ ## NAME = value; \
          emit NAME ## Changed(value); \
        } \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE m_ ## NAME;

#define CALL_THIS_IN_CONSTRACTEUR_FOR_AUTO_PROPERTY_SETTINGS \
for(int i = this->metaObject()->methodOffset(); \
    i < this->metaObject()->methodCount(); i++) \
{ \
    if(this->metaObject()->method(i).name().contains("_init")) \
        this->metaObject()->invokeMethod(this, \
                                         this->metaObject()->method(i).name(),\
                                         Qt::DirectConnection);\
}\


#define OUTPUT_GPIO_PROPERTY(NAME, wPInumberPIN) \
    Q_PROPERTY(bool NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
        Q_INVOKABLE void __init ## NAME() \
        {\
            pinMode( pin_ ## NAME , OUTPUT);\
        }\
       bool NAME() const { return m_ ## NAME ; } \
       void NAME(bool value) { \
          if (m_ ## NAME == value)  return; \
          m_ ## NAME = value; \
          emit NAME ## Changed(value); \
          if (value == true)  digitalWrite(wPInumberPIN, HIGH); \
          if (value == false)  digitalWrite(wPInumberPIN, LOW); \
        } \
       Q_SIGNAL void NAME ## Changed(bool value);\
    private: \
       int pin_ ## NAME = wPInumberPIN ; \
       bool m_ ## NAME;


#define INPUT_GPIO_PROPERTY(NAME, wPInumberPIN, INT_MODE, PUD_MODE) \
    Q_PROPERTY(bool NAME READ NAME NOTIFY NAME ## Changed ) \
    public: \
        static void __isrCatcher_ ## NAME() { QMetaObject::invokeMethod(MyGPIO::getInstance(), STRINGIFY(_gpio_read_ ## NAME), Qt::QueuedConnection);} \
        Q_INVOKABLE void __init ## NAME() \
        {\
            pinMode( pin_ ## NAME , INPUT);\
            wiringPiISR( pin_ ## NAME , INT_MODE , & __isrCatcher_ ## NAME );\
            pullUpDnControl( pin_ ## NAME , PUD_MODE );\
        }\
        bool NAME() { return m_ ## NAME ; } \
        void NAME(bool value) { \
          if (m_ ## NAME == value)  return; \
          m_ ## NAME = value; \
          emit NAME ## Changed(value); \
        } \
        Q_SIGNAL void NAME ## Changed(bool value);\
        Q_INVOKABLE void _gpio_read_ ## NAME() { \
               if( DEBUG_MODE ) qDebug() << Q_FUNC_INFO << " event on pin: " << pin_ ## NAME << " , pin name: " << STRINGIFY(NAME) \
                << " | old value = " << m_ ## NAME << " , new value is : " << (bool)digitalRead(pin_ ## NAME);\
                            NAME (digitalRead(pin_ ## NAME));} \
    private: \
       int pin_ ## NAME = wPInumberPIN ; \
       bool m_ ## NAME;
//#endif // MYPROPERTYHELPER_H
#define CALL_THIS_IN_CONSTRACTEUR_FOR_INPUT_OUTPUT_GPIO \
    wiringPiSetup();\
for(int i = this->metaObject()->methodOffset(); \
    i < this->metaObject()->methodCount(); i++) \
{ \
    if(this->metaObject()->method(i).name().contains("__init")) \
        this->metaObject()->invokeMethod(this, \
                                         this->metaObject()->method(i).name(),\
                                         Qt::DirectConnection);\
}

#define CONVERT_CLASS_INTO_SINGELTON(NAME) \
    static NAME *m_ ## NAME ;\
    static NAME *getInstance() { if ( !m_ ## NAME ) m_ ## NAME = new NAME(); return m_ ## NAME ;}
