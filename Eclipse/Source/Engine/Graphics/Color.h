#ifndef _GRAPHICS_COLOR_H_
#define _GRAPHICS_COLOR_H_

//////////////////////////////////////////////////////////
// Color 16
//////////////////////////////////////////////////////////
typedef unsigned short Color16;

char Color16GetR(Color16 color);
char Color16GetG(Color16 color);
char Color16GetB(Color16 color);

Color16 Color16SetR(Color16 color, unsigned short r);
Color16 Color16SetG(Color16 color, unsigned short g);
Color16 Color16SetB(Color16 color, unsigned short b);

Color16 Color16RGB(unsigned short r, unsigned short g, unsigned short b);
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Color 24
//////////////////////////////////////////////////////////
typedef struct Color24
{
    char R;
    char G;
    char B;
}
Color24;
//////////////////////////////////////////////////////////

#endif // !_GRAPHICS_COLOR_H_