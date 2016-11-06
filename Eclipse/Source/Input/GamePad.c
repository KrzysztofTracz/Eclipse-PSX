#include "GamePad.h"
#include "Manager.h"

#define BUTTON_PRINT_STATE(button, gamepad) FntPrint(gamepad->DebugStreamID, #button ":%s\n", BSToString(gamepad->button))

#define BUTTON_PRINT_PRESSED(button, gamepad) if(gamepad->button == BS_PRESSED) FntPrint(gamepad->DebugStreamID, #button "\n")

#define BUTTON_UPDATE_STATE(button, gamepad, device) gamePad->button = device->State.PadController.button \
                                                                     | (GamePadCheckButtonState(gamePad, BUTTON_TO_BUTTON_ENUM(button), device->State.PadController.button) == 0 ? 2 : 0)                                                                                                                                            

#define BUTTON_CLEAR_STATE(button, gamepad) gamePad->button = BS_RELEASED

void GamePadClear(GamePad* gamePad);

void GamePadInit(GamePad* gamePad, ControllerDeviceSlot slot)
{
    gamePad->Slot             = slot;
    gamePad->ConnectionStatus = GPCS_DISCONNECTED;
    gamePad->DebugStreamID    = 0;
    GamePadClear(gamePad);
}

GamePadConnectionStatus GamePadUpdate(GamePad* gamePad, ControllerDevice* device)
{
    GamePadConnectionStatus result = GPCS_UNKNOWN;

    if (device->Result == 0) 
    {
        result = gamePad->ConnectionStatus == GPCS_DISCONNECTED
               ? GPCS_WAS_CONNECTED
               : GPCS_CONNECTED;

        gamePad->ConnectionStatus = GPCS_CONNECTED;
        
        FOR_EACH_BUTTON(UPDATE_STATE, gamePad, device);
    }
    else
    {
        result = gamePad->ConnectionStatus == GPCS_CONNECTED
               ? GPCS_WAS_DISCONNECTED
               : GPCS_DISCONNECTED;

        gamePad->ConnectionStatus = GPCS_DISCONNECTED;
        GamePadClear(gamePad);
    }

    GampadPrintState(gamePad);

    return result;
}

void GamePadClear(GamePad* gamePad)
{
    FOR_EACH_BUTTON(CLEAR_STATE, gamePad);
}

void GampadPrintState(GamePad* gamePad)
{
    FntPrint(gamePad->DebugStreamID, "P%d\n", gamePad->Slot + 1);
    if (gamePad->ConnectionStatus == GPCS_DISCONNECTED)
    {
        FntPrint(gamePad->DebugStreamID, "**\n");
    }
    else
    {
        FntPrint(gamePad->DebugStreamID, "--\n");
        FOR_EACH_BUTTON(PRINT_PRESSED, gamePad);
    }    
}

int GamePadCheckButtonState(GamePad* gamePad, GamePadButton button, ButtonState state)
{
    int result = -1;

    ButtonState buttonState = GamePadGetButtonState(gamePad, button);

    switch (state)
    {
    case BS_PRESSED:
        result = buttonState == BS_PRESSED || 
                 buttonState == BS_WAS_PRESSED;
        break;
    case BS_RELEASED:
        result = buttonState == BS_RELEASED ||
                 buttonState == BS_WAS_RELEASED;
        break;
    default:
        result = buttonState == state;
        break;
    }

    return result;
}

ButtonState GamePadGetButtonState(GamePad* gamePad, GamePadButton button)
{
    switch (button)
    {
    case GPB_UP:
        return gamePad->UP;
    case GPB_DOWN:
        return gamePad->DOWN;
    case GPB_RIGHT:
        return gamePad->RIGHT;
    case GPB_LEFT:
        return gamePad->LEFT;
    case GPB_T:
        return gamePad->T;
    case GPB_X:
        return gamePad->X;
    case GPB_O:
        return gamePad->O;
    case GPB_S:
        return gamePad->S;
    case GPB_L1:
        return gamePad->L1;
    case GPB_L2:
        return gamePad->L2;
    case GPB_R1:
        return gamePad->R1;
    case GPB_R2:
        return gamePad->R2;
    case GPB_START:
        return gamePad->START;
    case GPB_SELECT:
        return gamePad->SELECT;
    default:
        return BS_UNKNOWN;
    }
}