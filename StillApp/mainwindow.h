#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}
class VaporTemperatureProbe;
class AnalogConverter;
class TemperaturePlotWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void updateVaporTemperature();
    void readSensors();

private:
    Ui::MainWindow *ui;
    QSharedPointer<VaporTemperatureProbe> m_vaporTemperatureProbe;
    QSharedPointer<AnalogConverter> m_analogConverter;
    QSharedPointer<TemperaturePlotWidget> m_temperaturePlot;
};

#endif // MAINWINDOW_H
