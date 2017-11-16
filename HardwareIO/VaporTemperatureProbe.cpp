#include "VaporTemperatureProbe.h"
#include <QDebug>
#include "DeviceUtilities.h"
#include "MAX31865.h"

VaporTemperatureProbe::VaporTemperatureProbe()
 {
    if(isDevice())
    {
        const int SPI_CHANNEL = 0;
        const int SPI_SPEED = 500000; //Hz
        m_hw.reset(new MAX31865(SPI_CHANNEL, SPI_SPEED));

        m_hw->init();

    }
    else
    {
        qDebug() << "running on desktop. simulating vapor probe hardware init ";
    }
}

float VaporTemperatureProbe::readTemperature()
{
    if(isDevice())
    {
        const float referenceResistor =  430.0;
        const float rtdNominalResistance = 100.0;
        int fault =  m_hw->readFault();
        qDebug() << "pre read fault code: " <<  fault;
        return m_hw->temperature(rtdNominalResistance,referenceResistor);
    }
    else
    {
         qDebug() << "running on desktop. simulating vapor probe temperature retrieval ";
        static float simulatedTemp = 77.0;
        if(simulatedTemp > 79){simulatedTemp = 77.0; }
        simulatedTemp += 0.3;
        return simulatedTemp;
    }
}
