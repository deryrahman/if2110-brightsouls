#ifndef _H_UI
#define _H_UI

#include "integer.h"
#include "graphics/terminal.h"
#include "graphics/pixel.h"

typedef enum {THINLINE, THICKLINE, MULTILINE} LineBorder;

void UIDrawBox(Terminal terminal, uint x, uint y, uint width, uint height, Pixel border1, Pixel border2, Pixel border3, Pixel border4, Pixel side1, Pixel side2, Pixel side3, Pixel side4);

void UIDrawBoxChar(Terminal terminal, uint x, uint y, uint width, uint height, Pixel character);
void UIDrawBoxLine(Terminal terminal, uint x, uint y, uint width, uint height, PixelStyle style, LineBorder border);

#endif
