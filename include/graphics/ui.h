#ifndef _H_UI
#define _H_UI

#include "integer.h"
#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/image.h"
#include "xstring.h"

typedef enum {THINLINE, THICKLINE, MULTILINE} LineBorder;

void UIDrawBox(Terminal terminal, uint x, uint y, uint width, uint height, Pixel border1, Pixel border2, Pixel border3, Pixel border4, Pixel side1, Pixel side2, Pixel side3, Pixel side4);

void UIDrawHLine(Terminal terminal, uint x, uint y, uint width, Pixel left, Pixel right, Pixel side);
void UIDrawVLine(Terminal terminal, uint x, uint y, uint height, Pixel top, Pixel bottom, Pixel side);

void UIDrawBoxChar(Terminal terminal, uint x, uint y, uint width, uint height, Pixel character);
void UIDrawBoxLine(Terminal terminal, uint x, uint y, uint width, uint height, PixelStyle style, LineBorder border);

void UIDrawText(Terminal terminal, uint x, uint y, PixelStyle style, String str);
void UIDrawElipsisText(Terminal terminal, uint x, uint y, uint maxChar, PixelStyle style, String str);
void UIDrawMultilineText(Terminal terminal, uint x, uint y, uint width, PixelStyle style, String str, boolean wordWrap);

void UIDrawImage(Terminal terminal, uint x, uint y, Image image);

#endif
