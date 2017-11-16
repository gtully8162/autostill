#ifndef TEMPERATUREPLOTWIDGET_H
#define TEMPERATUREPLOTWIDGET_H
#include <QList>
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
    void update(float datapoint);

private:
   QtCharts::QLineSeries *m_temperatureSeries;
   QtCharts::QChartView *m_chartView;
   QtCharts::QValueAxis *m_axisY;
   QtCharts::QValueAxis *m_axisX;
   QList <float> dataPoints;

};

#endif // TEMPERATUREPLOTWIDGET_H
