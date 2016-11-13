#include "Frame.h"

void GraphicsFrameInit(GraphicsFrame* frame)
{
    frame->OrderingTable.length = ORDERING_TABLE_LENGTH;
    frame->OrderingTable.org    = frame->OrderingTableTAG;

    GraphicsFrameClear(frame);
}

void GraphicsFrameClear(GraphicsFrame* frame)
{
    GsClearOt(0, 0, &frame->OrderingTable);
}

void GraphicsFrameClearColor(GraphicsFrame* frame, char r, char g, char b)
{
    GsSortClear(r, g, b, &frame->OrderingTable);
}

void GraphicsFrameDraw(GraphicsFrame* frame)
{
    GsDrawOt(&frame->OrderingTable);
}

void GraphicsFrameBind(GraphicsFrame* frame)
{
    GsSetWorkBase(frame->GPUPacketArea);
    GraphicsFrameClear(frame);
}