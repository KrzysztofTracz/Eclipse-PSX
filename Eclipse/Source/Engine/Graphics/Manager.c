#include "Manager.h"

GraphicsManager GGraphicsManager;

void GraphicsManagerInit()
{
    SetVideoMode(VIDEO_MODE);

    GsInitGraph(SCREEN_WIDTH,
                SCREEN_HEIGHT,
                GsNONINTER | GsOFSGPU,
                1, 0);

    GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);

    GraphicsFrameInit(&GGraphicsManager.FrameBuffers[0]);
    GraphicsFrameInit(&GGraphicsManager.FrameBuffers[1]);

    GGraphicsManager.CurrentFrameBuffer = GsGetActiveBuff();
}

void GraphicsManagerDraw()
{
    GraphicsFrameDraw(GraphicsManagerGetCurrentFrameBuffer());
}

void GraphicsManagerSwap(char r, char g, char b)
{   
    DrawSync(0);
    VSync(0);

    GsSwapDispBuff(); 
    GraphicsManagerSetCurrentFrameBuffer(GsGetActiveBuff());    
    GraphicsFrameClearColor(GraphicsManagerGetCurrentFrameBuffer(), 
                            r, g, b);
}

void GraphicsManagerSetCurrentFrameBuffer(char index)
{
    GGraphicsManager.CurrentFrameBuffer = GsGetActiveBuff();
    GraphicsFrameBind(GraphicsManagerGetCurrentFrameBuffer());
}

GraphicsFrame* GraphicsManagerGetCurrentFrameBuffer()
{
    return &GGraphicsManager.FrameBuffers[GGraphicsManager.CurrentFrameBuffer];
}