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
    m_temperaturePlot(new TemperaturePlotWidget)
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateVaporTemperature(const VaporTemperatureSample& sample)
{
    ui->currentVaporTemp->display(sample.fahrenheitValue());
    m_temperaturePlot->update(sample);
}
