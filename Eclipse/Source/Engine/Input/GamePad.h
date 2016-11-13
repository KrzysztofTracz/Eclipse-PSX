#ifndef _INPUT_GAMEPAD_H_
#define _INPUT_GAMEPAD_H_

#include "Device.h"

#define GAME_PAD_BUTTONS_AMOUNT 14

//////////////////////////////////////////////////////////
// Game Pad
//////////////////////////////////////////////////////////
typedef enum GamePadConnectionStatus
{
    GPCS_UNKNOWN          = -1,
    GPCS_DISCONNECTED     = 0,
    GPCS_CONNECTED        = 1,
    GPCS_WAS_CONNECTED    = 2,
    GPCS_WAS_DISCONNECTED = 3,
}
GamePadConnectionStatus;

typedef enum GamePadButton
{
    GPB_UNKNOWN = 0,
    GPB_UP      = 1,
    GPB_DOWN    = 2,
    GPB_RIGHT   = 4,
    GPB_LEFT    = 8,
    GPB_T       = 16,
    GPB_X       = 32,
    GPB_O       = 64,
    GPB_S       = 128,
    GPB_L1      = 256,
    GPB_L2      = 512,
    GPB_R1      = 1024,
    GPB_R2      = 2048,
    GPB_START   = 4096,
    GPB_SELECT  = 8192,
}
GamePadButton;

typedef struct GamePad
{
    char UP    : 2;
    char DOWN  : 2;
    char RIGHT : 2;
    char LEFT  : 2;

    char T : 2;
    char X : 2;
    char O : 2;
    char S : 2;

    char L1 : 2;
    char L2 : 2;
    char R1 : 2;
    char R2 : 2;

    char START  : 2;
    char SELECT : 2;

    char Slot             : 1;
    char ConnectionStatus : 1;

    long DebugStreamID;
} 
GamePad;

void GamePadInit     (GamePad* gamePad, ControllerDeviceSlot slot);
void GampadPrintState(GamePad* gamePad);

GamePadConnectionStatus GamePadUpdate(GamePad* gamePad, ControllerDevice* device);

ButtonState GamePadGetButtonState   (GamePad* gamePad, GamePadButton button);
int         GamePadCheckButtonsState(GamePad* gamePad, short buttons, ButtonState state);
int         GamePadCheckButtonState (GamePad* gamePad, GamePadButton button, ButtonState state);
//////////////////////////////////////////////////////////

#define BUTTON_TO_BUTTON_ENUM(button) GPB_##button

#define FOR_EACH_BUTTON(expression, ...) \
    BUTTON_##expression(UP, __VA_ARGS__); \
    BUTTON_##expression(DOWN, __VA_ARGS__); \
    BUTTON_##expression(RIGHT, __VA_ARGS__); \
    BUTTON_##expression(LEFT, __VA_ARGS__); \
    BUTTON_##expression(T, __VA_ARGS__); \
    BUTTON_##expression(X, __VA_ARGS__); \
    BUTTON_##expression(O, __VA_ARGS__); \
    BUTTON_##expression(S, __VA_ARGS__); \
    BUTTON_##expression(L1, __VA_ARGS__); \
    BUTTON_##expression(L2, __VA_ARGS__); \
    BUTTON_##expression(R1, __VA_ARGS__); \
    BUTTON_##expression(R2, __VA_ARGS__); \
    BUTTON_##expression(START, __VA_ARGS__); \
    BUTTON_##expression(SELECT, __VA_ARGS__);    


#endif // !_INPUT_GAMEPAD_H
