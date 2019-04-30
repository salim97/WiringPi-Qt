HEADERS += \
    $$PWD/mygpio.h \
    $$PWD/wiringPi-Qt.h

SOURCES += \
    $$PWD/mygpio.cpp

INCLUDEPATH += / usr / local / include
LIBS += -L/opt/qt5pi/sysroot/usr/lib -lwiringPi
