#ifndef TEMPERATUREPLOTWIDGET_H
#define TEMPERATUREPLOTWIDGET_H
namespace QtCharts
{
class QLineSeries;
class QChartView;
}

class TemperaturePlotWidget
{
public:
    TemperaturePlotWidget();
    QtCharts::QChartView* getView();

private:
   QtCharts::QLineSeries *m_temperatureSeries;
   QtCharts::QChartView *m_chartView;
};

#endif // TEMPERATUREPLOTWIDGET_H
