#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "StillAppController.h"
#include "DataStructures.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //start still controller on separate thread
    QThread controllerThread;
    StillAppController* controller = new StillAppController;
    controller->moveToThread(&controllerThread);
    QObject::connect(&controllerThread, SIGNAL(finished()), controller, SLOT(deleteLater()));
    QObject::connect(qApp, SIGNAL(aboutToQuit()), &controllerThread, SLOT(quit()));
    controllerThread.start();
    QMetaObject::invokeMethod( controller, "initialize", Qt::QueuedConnection);

    //start GUI
    MainWindow uiWindow;
    uiWindow.show();

    //connect events
    qRegisterMetaType< VaporTemperatureSample >("VaporTemperatureSample");
    QObject::connect(controller, SIGNAL(temperatureSampleAvailable(const VaporTemperatureSample&)), &uiWindow, SLOT(updateVaporTemperature(const VaporTemperatureSample&)));

    return a.exec();
}
