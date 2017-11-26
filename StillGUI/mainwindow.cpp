#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QDebug>
#include <QTimer>
#include <QSharedPointer>
#include <QtCharts/QChartView>
#include <QThread>
#include "TemperaturePlotWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_temperaturePlot(new TemperaturePlotWidget),
    m_vaporTemperatureSetPoint(150.0f)
{
    ui->setupUi(this);

    ui->chartWidget->setLayout(new QVBoxLayout());
    ui->chartWidget->layout()->addWidget(m_temperaturePlot->getView());

    ui->peakVaporTemp->display(m_vaporTemperatureSetPoint);
    QObject::connect(ui->vaporTemperatureUpButton, SIGNAL(clicked()), this, SLOT(incrementVaporSetpoint()));
    QObject::connect(ui->vaporTemperatureDownButton, SIGNAL(clicked()), this, SLOT(decrementVaporSetpoint()));
    //------------------------------------------
    //Tully brew logo
    QPixmap image(":/images/logo.jpg");
    QLabel* imageLabel = new QLabel();

    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    imageLabel->setPixmap(image);
    ui->logoWidget->setLayout(new QVBoxLayout());
    ui->logoWidget->layout()->addWidget(imageLabel);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::incrementVaporSetpoint()
{
    m_vaporTemperatureSetPoint += 0.1f;
    ui->setPointVaporTemp->display(m_vaporTemperatureSetPoint);
    emit newVaporSetPoint(m_vaporTemperatureSetPoint);
}
void MainWindow::decrementVaporSetpoint()
{
    m_vaporTemperatureSetPoint -= 0.1f;
    ui->setPointVaporTemp->display(m_vaporTemperatureSetPoint);
    emit newVaporSetPoint(m_vaporTemperatureSetPoint);
}

void MainWindow::updateVaporTemperature(const VaporTemperatureSample& sample)
{
    ui->currentVaporTemp->display(sample.fahrenheitValue());
    m_temperaturePlot->update(sample);

    float currentPeakTemp = ui->peakVaporTemp->value();
    if(currentPeakTemp < sample.fahrenheitValue())
    {
        ui->peakVaporTemp->display(sample.fahrenheitValue());
    }
}
