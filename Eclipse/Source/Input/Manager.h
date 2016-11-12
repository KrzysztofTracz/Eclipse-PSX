#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "Device.h"
#include "GamePad.h"

//////////////////////////////////////////////////////////
// Input Manager
//////////////////////////////////////////////////////////
typedef struct InputManager
{  
    ControllerDevice Devices[2];
    GamePad          GamePads[2];
}
InputManager;

void InputManagerInit();
void InputManagerFlushDebugStreams();

GamePadConnectionStatus InputManagerUpdateGamePad(ControllerDeviceSlot slot);

int P1Button(short buttons, ButtonState state);
int P2Button(short buttons, ButtonState state);

//////////////////////////////////////////////////////////

extern InputManager GInputManager;

#endif // !_INPUT_MANAGER_H_