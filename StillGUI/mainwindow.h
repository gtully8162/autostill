#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataStructures.h"

namespace Ui {
class MainWindow;
}
class TemperaturePlotWidget;
class VaporTemperatureSample;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void manuallySetBurnRate(float);
    void selectMode(OperationModeType);
    void selectAutoStillRun(AutoStillRunType);
public slots:
    void updateVaporTemperature(const VaporTemperatureSample& sample);
    void updateBurnRate(float burnRate);
private slots:
    void incrementVaporSetpoint();
    void decrementVaporSetpoint();
    void onTabSelected(int selectedTab);
private:
    Ui::MainWindow *ui;
    QSharedPointer<TemperaturePlotWidget> m_temperaturePlot;
    float m_vaporTemperatureSetPoint;
};

#endif // MAINWINDOW_H
