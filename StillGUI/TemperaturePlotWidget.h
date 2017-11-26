#ifndef TEMPERATUREPLOTWIDGET_H
#define TEMPERATUREPLOTWIDGET_H
#include <QList>
#include "DataStructures.h"
namespace QtCharts
{
class QLineSeries;
class QChartView;
class QValueAxis;
}

class TemperaturePlotWidget
{
public:
    TemperaturePlotWidget();
    QtCharts::QChartView* getView();
    void update(const VaporTemperatureSample& datapoint);

private:
   QtCharts::QLineSeries *m_temperatureSeries;
   QtCharts::QChartView *m_chartView;
   QtCharts::QValueAxis *m_axisY;
   QtCharts::QValueAxis *m_axisX;
   QList <float> dataPoints;

};

#endif // TEMPERATUREPLOTWIDGET_H
