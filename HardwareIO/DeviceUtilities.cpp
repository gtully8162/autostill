#include "DeviceUtilities.h"

bool isDevice()
{
#ifdef DESKTOP_BUILD
    return false;
#else
    return true;
#endif
}

void initializeDeviceHardware()
{
    if(isDevice())
    {
        wiringPiSetup();
    }
}
