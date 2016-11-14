#include "Engine.h"

EngineUpdateCallback UpdateCallback;

void EngineInit(EngineUpdateCallback updateCallback)
{
    UpdateCallback = updateCallback;

    GraphicsManagerInit();
    TimerManagerInit();
    LoggerInit();
    InputManagerInit();
}

int EngineStart()
{
    while (1)
    {
        TimerManagerTick();

        InputManagerUpdateGamePad(CDS_SLOT1);
        InputManagerUpdateGamePad(CDS_SLOT2);

        UpdateCallback();  

        LoggerFlush();
        InputManagerFlushDebugStreams();

        GraphicsManagerSwap(255, 0, 255);
		GraphicsManagerDraw();
    }

    return 0;
}