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
    m_currentBurnRate(0)
{
    ui->setupUi(this);

    ui->chartWidget->setLayout(new QVBoxLayout());
    ui->chartWidget->layout()->addWidget(m_temperaturePlot->getView());

    ui->burnRateIndicator->setValue(0);
    QObject::connect(ui->manualBurnRateUpButton, SIGNAL(clicked()), this, SLOT(incrementBurnRate()));
    QObject::connect(ui->manualBurnRateDownButton, SIGNAL(clicked()), this, SLOT(decrementBurnRate()));

     connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabSelected(int)));
    //------------------------------------------
    //Tully brew logo
    QPixmap image(":/images/logo.jpg");
    QLabel* imageLabel = new QLabel();

    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    imageLabel->setPixmap(image);
    ui->logoWidget->setLayout(new QVBoxLayout());
    ui->logoWidget->layout()->addWidget(imageLabel);

//    ui->autoMode->

}
void MainWindow::onTabSelected(int selectedTabIndex)
{
    if(selectedTabIndex == 0)
    {
        emit selectMode(AUTOSTILL_MODE);
    }
    else if(selectedTabIndex == 1)
    {
       emit selectMode(MANUAL_MODE) ;
    }
    else if(selectedTabIndex == 2)
    {
        emit selectMode(CALIBRATION_MODE);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::incrementBurnRate()
{
    if(m_currentBurnRate<100)
    {
        m_currentBurnRate++;
    }
    ui->burnRateIndicator->setValue(m_currentBurnRate);
    ui->burnRateIndicator2->setValue(m_currentBurnRate);

    emit burnRateManuallySet(m_currentBurnRate);
}
void MainWindow::decrementBurnRate()
{
    if(m_currentBurnRate>0)
    {
        m_currentBurnRate--;
    }
    ui->burnRateIndicator->setValue(m_currentBurnRate);
    ui->burnRateIndicator2->setValue(m_currentBurnRate);

    emit burnRateManuallySet(m_currentBurnRate);
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

void MainWindow::updateBurnRate(int burnRate)
{
    m_currentBurnRate = burnRate;
    ui->burnRateIndicator->setValue(burnRate);
    ui->burnRateIndicator2->setValue(burnRate);
}
