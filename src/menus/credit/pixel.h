#ifndef _H_PIXEL
#define _H_PIXEL

#include "wchar.h"

typedef enum {RESET = 0, BRIGHT = 1, DIM = 2, UNDERLINE = 3, BLINK = 4, REVERSE = 7, HIDDEN = 8} PixelAttribute;
typedef enum {DEFAULT = -1, BLACK = 0, RED = 1, GREEN = 2, YELLOW = 3, BLUE = 4, MAGENTA = 5, CYAN = 6, WHITE = 7} PixelColor;

typedef wchar_t wchar;

typedef struct {
    PixelAttribute attribute;
    PixelColor foreground;
    PixelColor background;
} PixelStyle;

typedef struct {
    PixelStyle style;
    wchar info;
} Pixel;

#define PixelInfo(x) (x).info
#define PixelStyle(x) (x).style
#define PixelBackground(x) (x).style.background
#define PixelForeground(x) (x).style.foreground
#define PixelAttribute(x) (x).style.attribute

#define PixelStyleAttribute(x) (x).attribute
#define PixelStyleForeground(x) (x).foreground
#define PixelStyleBackground(x) (x).background

void PixelStyleMake(PixelStyle *pixelStyle, PixelAttribute attribute, PixelColor background, PixelColor foreground);
void PixelStyleMakeDefault(PixelStyle *pixelStyle);

PixelStyle PixelStyleCreate(PixelAttribute attribute, PixelColor background, PixelColor foreground);
PixelStyle PixelStyleCreateDefault();

void PixelMakeEmpty(Pixel *pixel);
void PixelMakeDefault(Pixel *pixel, wchar info);
void PixelMake(Pixel* pixel, PixelAttribute attribute, PixelColor background, PixelColor foreground, wchar info);

Pixel PixelCreateEmpty();
Pixel PixelCreateDefault(wchar info);
Pixel PixelCreate(PixelAttribute attribute, PixelColor background, PixelColor foreground, wchar info);

void PixelPrint(Pixel pixel);

#endif
