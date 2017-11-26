#include "StillAppController.h"
#include "VaporTemperatureProbe.h"
#include "DataStructures.h"
#include "AnalogConverter.h"
#include "DataStructures.h"
#include "DeviceUtilities.h"
#include <QTimer>

StillAppController::StillAppController()
{
}
void StillAppController::initialize()
{
    initializeDeviceHardware();
    m_vaporTemperatureProbe.reset(new VaporTemperatureProbe);
    m_analogConverter.reset(new AnalogConverter);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readSensors()));
    timer->start(250); //time specified in ms
}

void StillAppController::readSensors()
{
    VaporTemperatureSample sample = m_vaporTemperatureProbe->readTemperature();
    emit temperatureSampleAvailable(sample);
}
