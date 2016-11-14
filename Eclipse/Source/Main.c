#include "Engine.h"

#include "Title.h"

u_long __ramsize   = 0x00200000; // force 2 megabytes of RAM
u_long __stacksize = 0x00004000; // force 16 kilobytes of stack

void Update();

//Image16* image;
Image24* image;

unsigned int ticks = 0;

int main()
{
    int i = 0;
	int j = 0;
    int x = 0;
    int y = 0;

    EngineInit(Update);
    
    //image = Image16Create(50, 50);
    //for (i = 0; i < image->BufferSize; i++)
    //{
    //    image->Buffer[i].R = i;
    //    image->Buffer[i].G = i;
    //    image->Buffer[i].B = i;
    //}
    //Image16Flush(image);

    //image = Image24Create(320, 240);
    //for (x = 0; x < image->Width; x++)
    //{
    //    for (y = 0; y < image->Height; y++)
    //    {
    //        Image24SetPixel(image, x, y, x, y, 0);
    //    }
    //}

	image = Image24Create(title_width, title_height);


    return EngineStart();
}

char FadeColor(int color, char fade)
{
	int value = color - fade;
	if (value < 0) value = 0;
	return value;
}

int fade = 255;

void Update()
{
	int i = 0;
	int j = 0;


	ticks++;

    if (P1Button(GPB_L1 | GPB_R1, BS_WAS_PRESSED) > 0)
    {
        LoggerClear();
    }

	fade-=25;
	if (fade < 0) fade = 0;

	for (i = 0; i < image->BufferSize; i++, j += 3)
	{
		image->Buffer[i].R = FadeColor(title[j	  ], fade);
		image->Buffer[i].G = FadeColor(title[j + 1], fade);
		image->Buffer[i].B = FadeColor(title[j + 2], fade);

		//image->Buffer[i].R = title[j];
		//image->Buffer[i].G = title[j + 1];
		//image->Buffer[i].B = title[j + 2];
	}

	Image24Flush(image);

    //Image16Draw(image, 100, 100);
    Image24Draw(image, 0, 0);
}