#include "Color.h"

char Color16GetR(Color16 color)
{
	return color & 31;
}

char Color16GetG(Color16 color)
{
	return (color & 992) >> 5;
}

char Color16GetB(Color16 color)
{
	return (color & 31744) >> 10;
}

Color16 Color16SetR(Color16 color, unsigned short r)
{
	return (color & ~31) | (r & 31);
}

Color16 Color16SetG(Color16 color, unsigned short g)
{
	return (color & ~992) | ((g << 5) & 992);
}

Color16 Color16SetB(Color16 color, unsigned short b)
{
	return (color & ~31744) | ((b << 10) & 31744);
}

Color16 Color16RGB(unsigned short r, unsigned short g, unsigned short b)
{
	return r | (g << 5) | (b << 10) | (1 << 15);
}