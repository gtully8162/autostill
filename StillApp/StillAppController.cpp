#include "StillAppController.h"
#include "VaporTemperatureProbe.h"
#include "DataStructures.h"
#include "AnalogConverter.h"
#include "DataStructures.h"
#include "DeviceUtilities.h"
#include <QTimer>
#include <QThread>

StillAppController::StillAppController():
    m_currentMode(AUTOSTILL_MODE)
{
}
void StillAppController::initialize()
{
    initializeDeviceHardware();
    m_vaporTemperatureProbe.reset(new VaporTemperatureProbe);
    m_analogConverter.reset(new AnalogConverter);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(execute()));
    timer->start(250); //time specified in ms
}

void StillAppController::execute()
{
    VaporTemperatureSample sample = m_vaporTemperatureProbe->readTemperature();
    m_burnRateAlgo.addTemperatureSample(sample);
    emit temperatureSampleAvailable(sample);
    if(m_currentMode == AUTOSTILL_MODE)
    {
        float calculatedBurnRate = m_burnRateAlgo.calculateBurnRate();
        emit calculatedBurnRateAvailable(calculatedBurnRate);
        setBurnRate(calculatedBurnRate);
    }
}

void StillAppController::setBurnRate(int burnRate)
{
    m_analogConverter->setOutputPercent(burnRate);
}

void StillAppController::onModeSelected(OperationModeType mode)
{
    m_currentMode = mode;
}

void StillAppController::onAutoStillRunSelected(AutoStillRunType selectedRun)
{
    m_burnRateAlgo.selectRun(selectedRun);
}
