#include "TemperaturePlotWidget.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

using namespace QtCharts;
TemperaturePlotWidget::TemperaturePlotWidget()
{

    m_temperatureSeries = new QLineSeries();

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(m_temperatureSeries);

    m_axisX = new QValueAxis;
    m_axisX->setLabelFormat("%g");
    m_axisX->setTitleText("Samples");

    m_axisY = new QValueAxis;
    m_axisY->setRange(100,200);
    chart->setAxisX(m_axisX, m_temperatureSeries);
    chart->setAxisY(m_axisY, m_temperatureSeries);
    chart->setTitle("Vapor Temperature with Respect to Time");
 //   chart->removeSeries;

    m_chartView = new QChartView(chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

}

void TemperaturePlotWidget::update(float datapoint)
{
//     dataPoints.push_back(datapoint);

    if(m_temperatureSeries->points().size() >= 20)
    {
        m_temperatureSeries->remove(0);
    }
    m_temperatureSeries->append(m_temperatureSeries->points().size(), datapoint);
    int first = m_temperatureSeries->points().first().rx();
    int last = m_temperatureSeries->points().last().rx();

    m_axisX->setRange(first, last);
    m_chartView->repaint();
}

QtCharts::QChartView* TemperaturePlotWidget::getView()
{
    return m_chartView;
}
