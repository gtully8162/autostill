#include "AnalogConverter.h"
#include <QDebug>
#include <QThread>
#include <wiringPi.h>
#include <pcf8591.h>
#include "DeviceUtilities.h"

const int PCF_BASE_PIN = 120;

AnalogConverter::AnalogConverter()
{
    if(isDevice())
    {
        const int i2cAddr =0x48;
        pcf8591Setup(PCF_BASE_PIN,  i2cAddr) ;
    }
}

void AnalogConverter::setOutputPercent(float percent)
{
    m_desiredPercentage = percent;

    int outputValue = 255*(percent/100.0);
    if(isDevice())
    {
        QThread::msleep(20);
        analogWrite(PCF_BASE_PIN, outputValue);
    }
    else
    {
        qDebug() << "running on desktop. simulating setting of valve voltage ";
    }
    qDebug() << "analog output set to: " <<  outputValue;
}

float AnalogConverter::readObservedVoltage()
{
    if(isDevice())
    {
//        int observedVoltage = analogRead(PCF_BASE_PIN) / 255 * REFERENCE_VOLTAGE;
        QThread::msleep(20);
        return 0;
    }
    else
    {
        qDebug() << "running on desktop. simulating observed valve voltage retrieval";
        return 0.0;
    }
}
