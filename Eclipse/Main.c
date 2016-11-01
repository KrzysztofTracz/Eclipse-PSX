#include <stdlib.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

#include "Input.h"

#define OT_LENGTH 1 // the ordertable length
#define PACKETMAX 18 // the maximum number of objects on the screen
#define SCREEN_WIDTH  320 // screen width
#define	SCREEN_HEIGHT 240 // screen height

GsOT myOT[2];
GsOT_TAG myOT_TAG[2][1 << OT_LENGTH];
PACKET GPUPacketArea[2][PACKETMAX];

u_long __ramsize   = 0x00200000; // force 2 megabytes of RAM
u_long __stacksize = 0x00004000; // force 16 kilobytes of stack

short CurrentBuffer = 0;



// ----------
// PROTOTYPES
// ----------
void graphics();
void display();

int main()
{
    int i;

	graphics(); // setup the graphics (seen below)
	FntLoad(960, 256); // load the font from the BIOS into VRAM/SGRAM
	//SetDumpFnt(FntOpen(5, 20, 320, 240, 0, 512)); // screen X,Y | max text length X,Y | autmatic background clear 0,1 | max characters

    InitInputManager();

	while (1) // draw and display forever
	{        
        PrintDeviceState(&GInputManager.Devices[0]);        
		display();
	}

	return 0;
}

void graphics()
{
    // within the BIOS, if the address 0xBFC7FF52 equals 'E', 
    // set it as PAL (1). Otherwise, set it as NTSC (0)
    SetVideoMode(*(char *)0xbfc7ff52 == 'E' ? 1 : 0);

	GsInitGraph(SCREEN_WIDTH, 
                SCREEN_HEIGHT, 
                GsNONINTER | GsOFSGPU, 
                1, 0);

    // set the top left coordinates of the two buffers in video memory
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT); 
    	                                          
    // init the ordering tables
	myOT[0].length = OT_LENGTH;
	myOT[1].length = OT_LENGTH;
	myOT[0].org = myOT_TAG[0];
	myOT[1].org = myOT_TAG[1];

	GsClearOt(0, 0, &myOT[0]);
	GsClearOt(0, 0, &myOT[1]);
}


void display()
{
    FlushInputDebugStream();
	FntFlush(-1); // refresh the font
	CurrentBuffer = GsGetActiveBuff(); // get the current buffer
	GsSetWorkBase((PACKET*)GPUPacketArea[CurrentBuffer]); // setup the packet workbase
	GsClearOt(0, 0, &myOT[CurrentBuffer]); // clear the ordering table
	DrawSync(0); // wait for all drawing to finish
	VSync(0); // wait for v_blank interrupt
	GsSwapDispBuff(); // flip the double buffers
	GsSortClear(50, 50, 50, &myOT[CurrentBuffer]); // clear the ordering table with a background color. RGB value 50,50,50 which is a grey background (0,0,0 would be black for example)
	GsDrawOt(&myOT[CurrentBuffer]); // Draw the ordering table for the CurrentBuffer
}