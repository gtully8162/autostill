#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void newVaporSetPoint(float desiredSetPoint);
public slots:
    void updateVaporTemperature(const VaporTemperatureSample& sample);
private slots:
    void incrementVaporSetpoint();
    void decrementVaporSetpoint();
private:
    Ui::MainWindow *ui;
    QSharedPointer<TemperaturePlotWidget> m_temperaturePlot;
    float m_vaporTemperatureSetPoint;
};

#endif // MAINWINDOW_H
