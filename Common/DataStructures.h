#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QTime>
#include <QMetaType>

enum OperationModeType{
    AUTOSTILL_MODE,
    MANUAL_MODE,
    CALIBRATION_MODE
};

enum AutoStillRunType
{
    HEADS_RUN,
    SPIRIT_RUN
};


class VaporTemperatureSample {

public:
    VaporTemperatureSample(){}
    VaporTemperatureSample(float temperature):
        m_temperature(temperature),
        m_sampleTime(QTime::currentTime())
    {
    }
    inline float fahrenheitValue() const { return m_temperature * 1.8 + 32; }
    inline int secondsElasped(){ return QTime::currentTime().secsTo(QTime::currentTime());}

private:
    float m_temperature;
    QTime m_sampleTime;

};

Q_DECLARE_METATYPE(VaporTemperatureSample)
Q_DECLARE_METATYPE(OperationModeType)
//

#endif // ANALOG_CONVERTER_H
