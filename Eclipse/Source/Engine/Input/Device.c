#include "Device.h"
#include "Manager.h"

const char* BSToString(ButtonState value)
{
    switch (value)
    {
    case BS_PRESSED:
        return "Pressed";
    case BS_RELEASED:
        return "Released";
    case BS_WAS_PRESSED:
        return "Was Pressed";
    case BS_WAS_RELEASED:
        return "Was Released";
    default:
        return "Unknown";
    }
}

const char* CDTToString(ControllerDeviceType value)
{
    switch (value)
    {
    case CDT_MOUSE:
        return "Mouse";
    case CDT_16BUTTON_ANALOG:
        return "16-Button Analog";
    case CDT_GUN_CONTROLLER:
        return "Gun Controller (Konami)";
    case CDT_16BUTTON:
        return "16-Button";
    case CDT_ANALOG_JOYSTICK:
        return "Analog Joystick";
    case CDT_GUN_CONTROLLER2:
        return "Gun Controller (Namco)";
    case CDT_ANALOG_CONTROLLER:
        return "Analog Controller";
    case CDT_MULTITAP:
        return "Multi Tap";
    default:
        return "Unknown";
    }
}