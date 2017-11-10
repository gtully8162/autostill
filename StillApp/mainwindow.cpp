#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QDebug>
#include <QTimer>
#include <QSharedPointer>
#include <QtCharts/QChartView>
#include "VaporTemperatureProbe.h"
#include "AnalogConverter.h"

#include "TemperaturePlotWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
  m_vaporTemperatureProbe(new VaporTemperatureProbe),
  m_analogConverter(new AnalogConverter)
{
    ui->setupUi(this);

    ui->chartWidget->setLayout(new QVBoxLayout());
    ui->chartWidget->layout()->addWidget(m_temperaturePlot->getView());

    //------------------------------------------
    //Tully brew logo
    QPixmap image(":/images/logo.jpg");
    QLabel* imageLabel = new QLabel();

    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    imageLabel->setPixmap(image);
    ui->logoWidget->setLayout(new QVBoxLayout());
    ui->logoWidget->layout()->addWidget(imageLabel);

//     QObject::connect(ui->vaporTemperatureUpButton, SIGNAL(clicked()), this, SLOT(updateVaporTemperature()));


     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(readSensors()));
     timer->start(250); //time specified in ms
      m_analogConverter->setValveVoltage(4.9);
}

void MainWindow::readSensors()
{
    float tempterature = m_vaporTemperatureProbe->readTemperature() * 1.8 + 32 ;
    ui->currentVaporTemp->display(tempterature);
    float voltage = m_analogConverter->readObervedValveVoltage();
    qDebug() << "current voltage: " << voltage;


}

void MainWindow::updateVaporTemperature()
{
//    float tempterature = m_vaporTemperatureProbe->readTemperature() * 1.8 + 32 ;
//    ui->currentVaporTemp->display(tempterature);
}

MainWindow::~MainWindow()
{
    delete ui;
}
