#ifndef _GRAPHICS_COLOR_H_
#define _GRAPHICS_COLOR_H_

typedef struct Color16
{
    char R : 5;
    char G : 6;
    char B : 5;
}
Color16;

typedef struct Color24
{
    char R;
    char G;
    char B;
}
Color24;

#endif // !_GRAPHICS_COLOR_H_