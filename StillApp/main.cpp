#include "mainwindow.h"
#include <QApplication>
#include "DeviceUtilities.h"

int main(int argc, char *argv[])
{   
    initializeDeviceHardware();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
