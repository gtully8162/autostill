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
//    m_axisX->setLabelFormat("%g");
//    m_axisX->setTitleText("Samples");

    m_axisY = new QValueAxis;

    chart->setAxisX(m_axisX, m_temperatureSeries);
    chart->setAxisY(m_axisY, m_temperatureSeries);
    chart->setTitle("Vapor Temperature with Respect to Time");
 //   chart->removeSeries;

    m_chartView = new QChartView(chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

}

bool pointYCoordinateLessThan(const QPointF& left, const QPointF& right)
{
    return left.y() < right.y();
}

void TemperaturePlotWidget::update(const VaporTemperatureSample& datapoint)
{
    if(m_temperatureSeries->points().size() >= 20)
    {
        m_temperatureSeries->remove(0);
    }
    //needed to continuously increment x coordinate
    static long xIncrement = 0;
    m_temperatureSeries->append(xIncrement++, datapoint.fahrenheitValue());

    //update axis range
    const QList<QPointF>& points = m_temperatureSeries->points();
    int first = points.first().x();
    int last = points.last().x();
    m_axisX->setRange(first, last);

    int minY = (std::min_element(points.begin(), points.end(), pointYCoordinateLessThan))->y();
    int maxY = (std::max_element(points.begin(), points.end(), pointYCoordinateLessThan))->y();
    m_axisY->setRange(minY-5,maxY+5);

    //update chart
    m_chartView->repaint();
}

QtCharts::QChartView* TemperaturePlotWidget::getView()
{
    return m_chartView;
}
