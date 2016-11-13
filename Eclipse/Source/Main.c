#include "Engine.h"

u_long __ramsize   = 0x00200000; // force 2 megabytes of RAM
u_long __stacksize = 0x00004000; // force 16 kilobytes of stack

void Update()
{
    if (P1Button(GPB_L1 | GPB_R1, BS_WAS_PRESSED) > 0)
    {
        LoggerClear();
    }
}

int main()
{
    EngineInit(Update);
    return EngineStart();
}

