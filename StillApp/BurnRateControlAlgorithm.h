#ifndef BURNRATCONTROLALGORITHM_H
#define BURNRATCONTROLALGORITHM_H

#include "DataStructures.h"
class BurnRateConrtrolAlgorithm
{
public:
    BurnRateConrtrolAlgorithm();
    void addTemperatureSample(const VaporTemperatureSample& VaporTemperatureSample);
    void selectRun(AutoStillRunType selectedRun);
    float calculateBurnRate();

private:

    QList<VaporTemperatureSample> m_dataPoints;
    AutoStillRunType m_selectedRun;


};

#endif // BURNRATCONTROLALGORITHM_H
