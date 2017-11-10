#include "AnalogConverter.h"
#include <QDebug>
#include <wiringPi.h>
#include <pcf8591.h>
#include "DeviceUtilities.h"

const int PCF_BASE_PIN = 120;
const float REFERENCE_VOLTAGE = 5.0;

AnalogConverter::AnalogConverter()
{
    if(isDevice())
    {
        const int i2cAddr =0x48;
        pcf8591Setup(PCF_BASE_PIN,  i2cAddr) ;
    }
}

void AnalogConverter::setValveVoltage(float voltage)
{
    m_desiredVoltage = voltage;
    if(isDevice())
    {
        int value = voltage / REFERENCE_VOLTAGE * 255;
        analogWrite(PCF_BASE_PIN, value);
    }
    else
    {
        qDebug() << "running on desktop. simulating setting of valve voltage ";
    }
}
//        if(abs(m_desiredVoltage - voltage) < .01)
float AnalogConverter::readObervedValveVoltage()
{
    if(isDevice())
    {
        int observedVoltage = analogRead(PCF_BASE_PIN) / 255 * REFERENCE_VOLTAGE;
//        adjustVoltage(observedVoltage);
        return observedVoltage;
    }
    else
    {
        qDebug() << "running on desktop. simulating observed valve voltage retrieval";
        return 0.0;
    }
}

//void AnalogConverter::adjustVoltage(float observedVoltage)
//{
//    float deltaVoltage = observedVoltage - m_desiredVoltage;


//    if(deltaVoltage > 0.0)
//    {

//    }
//    else if(deltaVoltage < 0.0)
//    {

//    }
//}
