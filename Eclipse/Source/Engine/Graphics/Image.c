#include "Image.h"
#include "Manager.h"


//////////////////////////////////////////////////////////
// Image 16
//////////////////////////////////////////////////////////
Image16* Image16Create(unsigned int width, unsigned int height)
{
    Image16* image = (Image16*)malloc(sizeof(Image16));

    image->Width = width;
    image->Height = height;

    image->VRAMPosition.x = SCREEN_WIDTH;
    image->VRAMPosition.y = 0;
    image->VRAMPosition.w = width;
    image->VRAMPosition.h = height;

    image->BufferSize = width * height;
    image->Buffer = (Color16*)malloc(image->BufferSize * sizeof(Color16));

    return image;
}

void Image16Destroy(Image16* image)
{
    free(image->Buffer);
    free(image);
}

unsigned int IImage16GetIndex(Image16* image, unsigned int x, unsigned int y)
{
    return x + (y * image->Height);
}

Color16 Image16GetPixel(Image16* image, unsigned int x, unsigned int y)
{
    return image->Buffer[IImage16GetIndex(image, x, y)];
}

void Image16SetPixel(Image16* image, unsigned int x, unsigned int y, Color16 color)
{
    image->Buffer[IImage16GetIndex(image, x, y)] = color;
}

void Image16Flush(Image16* image)
{
    LoadImage(&image->VRAMPosition, (u_long*)image->Buffer);
}

void Image16Draw(Image16* image, unsigned int x, unsigned int y)
{
    MoveImage(&image->VRAMPosition,
              GraphicsManagerGetDrawBufferX() + x,
              GraphicsManagerGetDrawBufferY() + y);
}
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Image 24
//////////////////////////////////////////////////////////
Image24* Image24Create(unsigned int width, unsigned int height)
{
    Image24* image = (Image24*)malloc(sizeof(Image24));
    
    image->Width  = width;
    image->Height = height;
    
    image->VRAMPosition.x = SCREEN_WIDTH * 3 / 2;
    image->VRAMPosition.y = 0;
    image->VRAMPosition.w = width * 3 / 2;
    image->VRAMPosition.h = height;

    image->BufferSize = width * height;
    image->Buffer     = (Color24*)malloc(image->BufferSize * sizeof(Color24));

    return image;
} 

void Image24Destroy(Image24* image)
{
    free(image->Buffer);
    free(image);
}

unsigned int Image24GetIndex(Image24* image, unsigned int x, unsigned int y)
{
    return x + (y * image->Width);
}

Color24 Image24GetPixel(Image24* image, unsigned int x, unsigned int y)
{
    return image->Buffer[Image24GetIndex(image, x, y)];
}

void Image24SetPixel(Image24* image, unsigned int x, unsigned int y, char r, char g, char b)
{
    image->Buffer[Image24GetIndex(image, x, y)].R = r;
    image->Buffer[Image24GetIndex(image, x, y)].G = g;
    image->Buffer[Image24GetIndex(image, x, y)].B = b;
}

void Image24Flush(Image24* image)
{
    LoadImage2(&image->VRAMPosition, (u_long*)image->Buffer);
}

void Image24Draw(Image24* image, unsigned int x, unsigned int y)
{
    MoveImage2(&image->VRAMPosition,
              GraphicsManagerGetDrawBufferX() + x, 
              GraphicsManagerGetDrawBufferY() + y);
}
//////////////////////////////////////////////////////////