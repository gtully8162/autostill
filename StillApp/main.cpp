#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "StillAppController.h"
#include "DataStructures.h"
int main(int argc, char *argv[])
{   
    QThread controllerThread;
    StillAppController* controller = new StillAppController;
    controller->moveToThread(&controllerThread);
    QObject::connect(&controllerThread, SIGNAL(finished()), controller, SLOT(deleteLater()));
    controllerThread.start();

    QMetaObject::invokeMethod( controller, "initialize", Qt::QueuedConnection);
    QApplication a(argc, argv);
    MainWindow uiWindow;
    uiWindow.show();

    qRegisterMetaType< VaporTemperatureSample >("VaporTemperatureSample");
    QObject::connect(controller, SIGNAL(temperatureSampleAvailable(const VaporTemperatureSample&)), &uiWindow, SLOT(updateVaporTemperature(const VaporTemperatureSample&)));

    return a.exec();
}
