#include <stdlib.h>
#include <libgte.h>
#include "Input.h"

#define DEBUG_STREAM_AREA_X 5
#define DEBUG_STREAM_AREA_Y 5
#define DEBUG_STREAM_AREA_WIDTH 320
#define DEBUG_STREAM_AREA_HEIGHT 240
#define DEBUG_STREAM_CHARS_LIMIT 512

//#define PRINT_BUTTON_STATUS(button, deviceState) FntPrint(GInputManager.DebugStreamID, "%s:" #button "\n", deviceState->button == BSPressed ? "x" : " ");
#define PRINT_BUTTON_STATUS(button, deviceState) if(deviceState->button == BSPressed) FntPrint(GInputManager.DebugStreamID, #button "\n");

InputManager GInputManager;

void InitInputManager()
{
    InitInputDebugStream();

    GInputManager.Devices[0].Slot = 0;
    GInputManager.Devices[1].Slot = 1;

    InitPAD(&GInputManager.Devices[0], DEVICE_STATE_BUFFER_LENGTH,
            &GInputManager.Devices[1], DEVICE_STATE_BUFFER_LENGTH);
    
    StartPAD();
}

void InitInputDebugStream()
{
    GInputManager.DebugStreamID = FntOpen(DEBUG_STREAM_AREA_X,
                                          DEBUG_STREAM_AREA_Y,
                                          DEBUG_STREAM_AREA_WIDTH,
                                          DEBUG_STREAM_AREA_HEIGHT,
                                          0,
                                          DEBUG_STREAM_CHARS_LIMIT);

    SetDumpFnt(GInputManager.DebugStreamID);
}

void FlushInputDebugStream()
{
    FntFlush(GInputManager.DebugStreamID);
}

const char* BSToString(ButtonState value)
{
    switch (value)
    {
    case BSPressed:
        return "Pressed";
    case BSReleased:
        return "Released";
    case BSWasPressed:
        return "Was Pressed";
    case BSWasReleased:
        return "Was Released";
    default:
        return "Unknown";
    }
}

const char* CDTToString(ControllerDeviceType value)
{
    switch (value)
    {
    case CDTMouse:
        return "Mouse";
    case CDT16ButtonAnalog:
        return "16-Button Analog";
    case CDTGunController:
        return "Gun Controller (Konami)";
    case CDT16Button:
        return "16-Button";
    case CDTAnalogJoystick:
        return "Analog Joystick";
    case CDTGunController2:
        return "Gun Controller (Namco)";
    case CDTAnalogController:
        return "Analog Controller";
    case CDTMultiTap:
        return "Multi Tap";
    default:
        return "Unknown";
    }
}

void PrintDeviceState(ControllerDevice* device)
{
    FntPrint(GInputManager.DebugStreamID, "Input:P%d\n--------\n", device->Slot + 1);
    
    switch (device->Type)
    {
    case CDT16Button:
    case CDTAnalogJoystick:
    case CDTAnalogController:
        PrintPadControllerState(&device->State.PadController);
        break;
    }
}

void PrintPadControllerState(PadControllerState* padControllerState)
{
    PRINT_BUTTON_STATUS(UP, padControllerState);
    PRINT_BUTTON_STATUS(DOWN, padControllerState);
    PRINT_BUTTON_STATUS(LEFT, padControllerState);
    PRINT_BUTTON_STATUS(RIGHT, padControllerState);

    PRINT_BUTTON_STATUS(T, padControllerState);
    PRINT_BUTTON_STATUS(O, padControllerState);
    PRINT_BUTTON_STATUS(S, padControllerState);
    PRINT_BUTTON_STATUS(X, padControllerState);

    PRINT_BUTTON_STATUS(SELECT, padControllerState);
    PRINT_BUTTON_STATUS(START, padControllerState);

    PRINT_BUTTON_STATUS(L1, padControllerState);
    PRINT_BUTTON_STATUS(R1, padControllerState);

    PRINT_BUTTON_STATUS(L2, padControllerState);
    PRINT_BUTTON_STATUS(R2, padControllerState);

    PRINT_BUTTON_STATUS(L3, padControllerState);
    PRINT_BUTTON_STATUS(R3, padControllerState);
}