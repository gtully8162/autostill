#ifndef ANALOG_CONVERTER_H
#define ANALOG_CONVERTER_H

class AnalogConverter
{
public:

    AnalogConverter();

    void setOutputPercent(float percent);
    float readObservedVoltage();

private:
    float m_desiredPercentage;
};


#endif // ANALOG_CONVERTER_H
