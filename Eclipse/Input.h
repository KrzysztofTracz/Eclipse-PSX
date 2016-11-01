#ifndef _INPUT_H_
#define _INPUT_H_

#define DEVICE_STATE_BUFFER_LENGTH 34
#define DEVICE_STATE_HEADER 2

//////////////////////////////////////////////////////////
// Pad Controller State
//////////////////////////////////////////////////////////
typedef enum ButtonState
{
    BSPressed     = 0,
    BSReleased    = 1,
    BSWasPressed  = 2,
    BSWasReleased = 3
} 
ButtonState;

const char* BSToString(ButtonState value);

typedef struct PadControllerState
{
    char SELECT : 1;
    char L3     : 1;
    char R3     : 1;
    char START  : 1;

    char UP     : 1;
    char RIGHT  : 1;
    char DOWN   : 1;
    char LEFT   : 1;

    char L2 : 1;
    char R2 : 1;
    char L1 : 1;
    char R1 : 1;

    char T : 1;
    char O : 1;
    char X : 1;
    char S : 1;
} 
PadControllerState;

void PrintPadControllerState(PadControllerState* padControllerState);
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Controller Device State
//////////////////////////////////////////////////////////
typedef union ControllerDeviceState
{
    PadControllerState PadController;
    char RawBuffer[DEVICE_STATE_BUFFER_LENGTH - DEVICE_STATE_HEADER];

}
ControllerDeviceState;
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Controller Device
//////////////////////////////////////////////////////////
typedef enum ControllerDeviceType
{
    CDTMouse            = 1,
    CDT16ButtonAnalog   = 2,
    CDTGunController    = 3,
    CDT16Button         = 4,
    CDTAnalogJoystick   = 5,
    CDTGunController2   = 6,
    CDTAnalogController = 7,
    CDTMultiTap         = 8
} 
ControllerDeviceType;

const char* CDTToString(ControllerDeviceType value);

typedef struct ControllerDevice
{
    char Result;
    char BytesReceived : 4;
    ControllerDeviceType Type : 4;
    
    ControllerDeviceState State;
    
    char Slot : 1;
}
ControllerDevice;

void PrintDeviceState(ControllerDevice* device);
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Input Manager
//////////////////////////////////////////////////////////
typedef struct InputManager
{
    int DebugStreamID;
    ControllerDevice Devices[2];
} 
InputManager;

void InitInputManager();
void FlushInputDebugStream();
//////////////////////////////////////////////////////////

extern InputManager GInputManager;

#endif // !_INPUT_H_
