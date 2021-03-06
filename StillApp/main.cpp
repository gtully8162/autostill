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

    qRegisterMetaType< VaporTemperatureSample >("VaporTemperatureSample");
    qRegisterMetaType< OperationModeType >("OperationModeType");

    //ui output events
    QObject::connect(controller, SIGNAL(temperatureSampleAvailable(VaporTemperatureSample)), &uiWindow, SLOT(updateVaporTemperature(const VaporTemperatureSample&)));
    QObject::connect(controller, SIGNAL(calculatedBurnRateAvailable(int)), &uiWindow, SLOT(updateBurnRate(int)));

    //user input events
    QObject::connect(&uiWindow, SIGNAL(burnRateManuallySet(int)), controller, SLOT(setBurnRate(int)));
    QObject::connect(&uiWindow, SIGNAL(selectAutoStillRun(AutoStillRunType)), controller, SLOT(onAutoStillRunSelected(AutoStillRunType)));
    QObject::connect(&uiWindow, SIGNAL(selectMode(OperationModeType)), controller, SLOT(onModeSelected(OperationModeType)));

    return a.exec();
}
