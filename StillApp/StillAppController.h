#ifndef STILLAPPCONTROLLER_H
#define STILLAPPCONTROLLER_H

#include <QSharedPointer>
#include <QObject>
#include "DataStructures.h"
#include "BurnRateControlAlgorithm.h"
class VaporTemperatureProbe;
class AnalogConverter;
class VaporTemperatureSample;

class StillAppController: public QObject{
    Q_OBJECT
public:
    StillAppController();

public slots:
    void initialize();
    void onModeSelected(OperationModeType);
    void onAutoStillRunSelected(AutoStillRunType);
    void setBurnRate(float burnRate);

signals:
    void temperatureSampleAvailable(VaporTemperatureSample sample);
    void calculatedBurnRateAvailable(float burnRate);

private slots:
    void execute();

private:

    QSharedPointer<VaporTemperatureProbe> m_vaporTemperatureProbe;
    QSharedPointer<AnalogConverter> m_analogConverter;
    BurnRateConrtrolAlgorithm m_burnRateAlgo;

    OperationModeType m_currentMode;

};


#endif // STILLAPPCONTROLLER_H
