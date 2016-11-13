#ifndef _GRAPHICS_FRAME_BUFFER_H_
#define _GRAPHICS_FRAME_BUFFER_H_

#include <stdlib.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

#define ORDERING_TABLE_LENGTH 1
#define PACKET_MAX 18

//////////////////////////////////////////////////////////
// Frame Buffer
//////////////////////////////////////////////////////////
typedef struct GraphicsFrame
{
    GsOT     OrderingTable;
    GsOT_TAG OrderingTableTAG[1 << ORDERING_TABLE_LENGTH];
    
    PACKET GPUPacketArea[PACKET_MAX];
}
GraphicsFrame;

void GraphicsFrameInit(GraphicsFrame* frame);
void GraphicsFrameClear(GraphicsFrame* frame);
void GraphicsFrameClearColor(GraphicsFrame* frame, char r, char g, char b);
void GraphicsFrameDraw(GraphicsFrame* frame);
void GraphicsFrameBind(GraphicsFrame* frame);

//////////////////////////////////////////////////////////

#endif // !_GRAPHICS_FRAME_BUFFER_H_