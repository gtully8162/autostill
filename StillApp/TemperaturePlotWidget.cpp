#include "TemperaturePlotWidget.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

using namespace QtCharts;
TemperaturePlotWidget::TemperaturePlotWidget()
{

    m_temperatureSeries = new QLineSeries();

    m_temperatureSeries->append(0, 6);
    m_temperatureSeries->append(2, 4);
    m_temperatureSeries->append(3, 8);
    m_temperatureSeries->append(7, 4);
    m_temperatureSeries->append(10, 5);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(m_temperatureSeries);

    chart->createDefaultAxes();
    chart->setTitle("Vapor Temperature with Respect to Time");


    m_chartView = new QChartView(chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

}


QtCharts::QChartView* TemperaturePlotWidget::getView()
{
    return m_chartView;
}
