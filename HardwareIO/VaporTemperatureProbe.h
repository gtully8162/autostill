#ifndef HARDWAREIO_H
#define HARDWAREIO_H

#include <QSharedPointer>
#include "DataStructures.h"

class MAX31865;
class VaporTemperatureProbe
{

public:
    VaporTemperatureProbe();
    VaporTemperatureSample readTemperature();

private:
   QSharedPointer<MAX31865> m_hw;
};

#endif // HARDWAREIO_H
