#ifndef _GRAPHICS_MANAGER_H_
#define _GRAPHICS_MANAGER_H_

#include "Frame.h"

#define SCREEN_WIDTH  320
#define	SCREEN_HEIGHT 240

//////////////////////////////////////////////////////////
// Video Mode
//////////////////////////////////////////////////////////
typedef enum VideoMode
{
    VM_NTSC = 0,
    VM_PAL  = 1
}
VideoMode;

#ifdef _NTSC   
    #define VIDEO_MODE VM_NTSC
#elif _PAL
    #define VIDEO_MODE VM_PAL
#endif
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Graphics Manager
//////////////////////////////////////////////////////////
typedef struct GraphicsManager
{
    GraphicsFrame FrameBuffers[2];

    char CurrentFrameBuffer : 1;    
}
GraphicsManager;

void GraphicsManagerInit();
void GraphicsManagerDraw();
void GraphicsManagerSwap(char r, char g, char b);

           void GraphicsManagerSetCurrentFrameBuffer(char index);
GraphicsFrame*  GraphicsManagerGetCurrentFrameBuffer();

unsigned int GraphicsManagerGetDrawBufferX();
unsigned int GraphicsManagerGetDrawBufferY();

//////////////////////////////////////////////////////////

extern GraphicsManager GGraphicsManager;

#endif // !_GRAPHICS_MANAGER_H_