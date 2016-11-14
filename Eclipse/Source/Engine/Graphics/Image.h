#ifndef _GRAPHICS_IMAGE_H_
#define _GRAPHICS_IMAGE_H_

#include <stdlib.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

#include "Color.h"


//////////////////////////////////////////////////////////
// Image 16
//////////////////////////////////////////////////////////
typedef struct Image16
{
    unsigned short* Buffer;
    unsigned int BufferSize;
    RECT VRAMPosition;
    unsigned int Width;
    unsigned int Height;
}
Image16;

Image16* Image16Create(unsigned int width, unsigned int height);
    void Image16Destroy(Image16* image);

unsigned short Image16GetPixel(Image16* image, unsigned int x, unsigned int y);
   void Image16SetPixel(Image16* image, unsigned int x, unsigned int y, unsigned short color);
   void Image16Flush(Image16* image);

void Image16Draw(Image16* image, unsigned int x, unsigned int y);
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Image 24
//////////////////////////////////////////////////////////
typedef struct Image24
{
    Color24* Buffer;
    unsigned int BufferSize;
    RECT VRAMPosition;
    unsigned int Width;
    unsigned int Height;
}
Image24;

Image24* Image24Create(unsigned int width, unsigned int height);
    void Image24Destroy(Image24* image);

Color24 Image24GetPixel(Image24* image, unsigned int x, unsigned int y);
   void Image24SetPixel(Image24* image, unsigned int x, unsigned int y, char r, char g, char b);
   void Image24Flush   (Image24* image);

void Image24Draw(Image24* image, unsigned int x, unsigned int y);
//////////////////////////////////////////////////////////


#endif // !_GRAPHICS_IMAGE_H_