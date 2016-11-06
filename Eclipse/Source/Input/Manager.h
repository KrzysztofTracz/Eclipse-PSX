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

ButtonState P1Button(GamePadButton button);
ButtonState P2Button(GamePadButton button);

//////////////////////////////////////////////////////////

extern InputManager GInputManager;

#endif // !_INPUT_MANAGER_H_