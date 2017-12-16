#include "BurnRateControlAlgorithm.h"

BurnRateConrtrolAlgorithm::BurnRateConrtrolAlgorithm() :
    m_selectedRun(HEADS_RUN)
{
}
void BurnRateConrtrolAlgorithm::addTemperatureSample(const VaporTemperatureSample& sample)
{
    m_dataPoints.push_back(sample);

    if(m_dataPoints.size() > 50)
    {
        m_dataPoints.pop_front();
    }
}

void BurnRateConrtrolAlgorithm::selectRun(AutoStillRunType selectedRun)
{
    m_selectedRun = selectedRun;
}

float BurnRateConrtrolAlgorithm::calculateBurnRate()
{
    return 0.0;
}
