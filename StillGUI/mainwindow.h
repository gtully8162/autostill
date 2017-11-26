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

public slots:
    void updateVaporTemperature(const VaporTemperatureSample& sample);

private:
    Ui::MainWindow *ui;
    QSharedPointer<TemperaturePlotWidget> m_temperaturePlot;
};

#endif // MAINWINDOW_H
