#include <stdlib.h>
#include <libgte.h>
#include "Manager.h"

InputManager GInputManager;

#define DEBUG_STREAM_AREA_X 0
#define DEBUG_STREAM_AREA_Y 5
#define DEBUG_STREAM_AREA_WIDTH 45
#define DEBUG_STREAM_AREA_HEIGHT 120
#define DEBUG_STREAM_CHARS_LIMIT 128

void InputManagerInitDebugStreams()
{
#ifdef _DEBUG
    GInputManager.GamePads[CDS_SLOT1].DebugStreamID = FntOpen(DEBUG_STREAM_AREA_X,
                                                              DEBUG_STREAM_AREA_Y,
                                                              DEBUG_STREAM_AREA_WIDTH,
                                                              DEBUG_STREAM_AREA_HEIGHT,
                                                              0,
                                                              DEBUG_STREAM_CHARS_LIMIT);

    SetDumpFnt(GInputManager.GamePads[CDS_SLOT1].DebugStreamID);

    GInputManager.GamePads[CDS_SLOT2].DebugStreamID = FntOpen(320 - DEBUG_STREAM_AREA_WIDTH - DEBUG_STREAM_AREA_X,
                                                              DEBUG_STREAM_AREA_Y,
                                                              DEBUG_STREAM_AREA_WIDTH,
                                                              DEBUG_STREAM_AREA_HEIGHT,
                                                              0,
                                                              DEBUG_STREAM_CHARS_LIMIT);

    SetDumpFnt(GInputManager.GamePads[CDS_SLOT2].DebugStreamID);
#endif
}

void InputManagerInit()
{
    GInputManager.Devices[CDS_SLOT1].Slot = CDS_SLOT1;
    GInputManager.Devices[CDS_SLOT2].Slot = CDS_SLOT2;

    InitPAD(&GInputManager.Devices[CDS_SLOT1], DEVICE_STATE_BUFFER_LENGTH,
            &GInputManager.Devices[CDS_SLOT2], DEVICE_STATE_BUFFER_LENGTH);
    
    StartPAD();

    GamePadInit(&GInputManager.GamePads[CDS_SLOT1], CDS_SLOT1);
    GamePadInit(&GInputManager.GamePads[CDS_SLOT2], CDS_SLOT2);

    InputManagerInitDebugStreams();
}

void InputManagerFlushDebugStreams()
{
#ifdef _DEBUG
    FntFlush(GInputManager.GamePads[CDS_SLOT1].DebugStreamID);
    FntFlush(GInputManager.GamePads[CDS_SLOT2].DebugStreamID);
#endif
}

GamePadConnectionStatus InputManagerUpdateGamePad(ControllerDeviceSlot slot)
{
    return GamePadUpdate(&GInputManager.GamePads[slot], 
                         &GInputManager.Devices [slot]);
}

int P1Button(short buttons, ButtonState state)
{
    return GamePadCheckButtonsState(&GInputManager.GamePads[CDS_SLOT1], buttons, state);
}

int P2Button(short buttons, ButtonState state)
{
    return GamePadCheckButtonsState(&GInputManager.GamePads[CDS_SLOT1], buttons, state);
}