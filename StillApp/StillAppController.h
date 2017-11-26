#ifndef STILLAPPCONTROLLER_H
#define STILLAPPCONTROLLER_H

#include <QSharedPointer>
#include <QObject>
class VaporTemperatureProbe;
class AnalogConverter;
class VaporTemperatureSample;

class StillAppController: public QObject{
    Q_OBJECT
public:
    StillAppController();
public slots:
    void initialize();
signals:
    void temperatureSampleAvailable(const VaporTemperatureSample& sample);

private slots:
    void readSensors();

private:
    QSharedPointer<VaporTemperatureProbe> m_vaporTemperatureProbe;
    QSharedPointer<AnalogConverter> m_analogConverter;

};


#endif // STILLAPPCONTROLLER_H
