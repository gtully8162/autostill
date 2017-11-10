#ifndef ANALOG_CONVERTER_H
#define ANALOG_CONVERTER_H

class AnalogConverter
{
public:

    AnalogConverter();

    void setValveVoltage(float voltage);
    float readObervedValveVoltage();

private:
    float m_desiredVoltage;
};


#endif // ANALOG_CONVERTER_H
