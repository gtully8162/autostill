#ifndef HARDWAREIO_H
#define HARDWAREIO_H

#include <QSharedPointer>

class MAX31865;
class VaporTemperatureProbe
{

public:
    VaporTemperatureProbe();
    float readTemperature();

private:
   QSharedPointer<MAX31865> m_hw;
};

#endif // HARDWAREIO_H
