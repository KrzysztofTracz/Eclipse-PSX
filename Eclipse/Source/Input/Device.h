#ifndef _INPUT_DEVICE_H_
#define _INPUT_DEVICE_H_

#define DEVICE_STATE_BUFFER_LENGTH 34
#define DEVICE_STATE_HEADER 2

//////////////////////////////////////////////////////////
// Pad Controller State
//////////////////////////////////////////////////////////
typedef enum ButtonState
{
    BS_UNKNOWN      = -1,
    BS_PRESSED      = 0,
    BS_RELEASED     = 1,
    BS_WAS_PRESSED  = 2,
    BS_WAS_RELEASED = 3,
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
typedef enum ControllerDeviceSlot
{
    CDS_UNKNOWN = -1,
    CDS_SLOT1   = 0,
    CDS_SLOT2   = 1
}
ControllerDeviceSlot;

typedef enum ControllerDeviceType
{
    CDT_UNKNOWN           = -1,
    CDT_MOUSE             = 1,
    CDT_16BUTTON_ANALOG   = 2,
    CDT_GUN_CONTROLLER    = 3,
    CDT_16BUTTON          = 4,
    CDT_ANALOG_JOYSTICK   = 5,
    CDT_GUN_CONTROLLER2   = 6,
    CDT_ANALOG_CONTROLLER = 7,
    CDT_MULTITAP          = 8
} 
ControllerDeviceType;

const char* CDTToString(ControllerDeviceType value);

typedef struct ControllerDevice
{
    char Result;
    char BytesReceived : 4;
    char Type          : 4;
 
    ControllerDeviceState State;
    
    char Slot : 1;
}
ControllerDevice;

//////////////////////////////////////////////////////////

#endif // !_INPUT_DEVICE_H_
