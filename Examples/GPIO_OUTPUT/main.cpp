#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <mygpio.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //no need to declare mygpio class because it's already singelton
    //you can get it directly;
    // MyGPIO *mygpio = MyGPIO::getInstance()

    //share myGPIO class with qml
    engine.rootContext()->setContextProperty("myGPIO", MyGPIO::getInstance());


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
