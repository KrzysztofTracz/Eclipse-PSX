#include "Engine.h"

#include "Title.h"

u_long __ramsize   = 0x00200000; // force 2 megabytes of RAM
u_long __stacksize = 0x00004000; // force 16 kilobytes of stack

void Update();

Image16* image;

int main()
{
    int i = 0;
	int j = 0;
    int x = 0;
    int y = 0;

    EngineInit(Update);

	image = Image16Create(title_width, title_height);


    return EngineStart();
}

unsigned short FadeColor(unsigned short color, unsigned short fade)
{
	unsigned short r = Color16GetR(color);
	unsigned short g = Color16GetG(color);
	unsigned short b = Color16GetB(color);

	r = fade > r ? 0 : r - fade;
	g = fade > g ? 0 : g - fade;
	b = fade > b ? 0 : b - fade;

	color = Color16RGB(r, g, b);

	return color;
}

int fade = 33;

void Update()
{
	int i = 0;

    if (P1Button(GPB_L1 | GPB_R1, BS_WAS_PRESSED) > 0)
    {
        LoggerClear();
    }

	fade-=3;
	if (fade >= 0)
	{
		for (i = 0; i < image->BufferSize; i++)
		{
			image->Buffer[i] = FadeColor(title[i], fade);
		}
		Image16Flush(image);
	}
	else
	{
		fade = -1;
	}
	
    Image16Draw(image, 0, 0);
}