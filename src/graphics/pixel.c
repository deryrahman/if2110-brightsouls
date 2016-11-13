#include "graphics/pixel.h"
#include <stdio.h>

void PixelStyleMake(PixelStyle *pixelStyle, PixelAttribute attribute, PixelColor background, PixelColor foreground) {
    PixelStyleAttribute(*pixelStyle) = attribute;
    PixelStyleForeground(*pixelStyle) = foreground;
    PixelStyleBackground(*pixelStyle) = background;
}

void PixelStyleMakeDefault(PixelStyle *pixelStyle) {
    PixelStyleMake(pixelStyle, RESET, DEFAULT, WHITE);
}

PixelStyle PixelStyleCreate(PixelAttribute attribute, PixelColor background, PixelColor foreground) {
    PixelStyle pixelStyle;
    PixelStyleMake(&pixelStyle, attribute, background, foreground);
    return pixelStyle;
}

PixelStyle PixelStyleCreateDefault() {
    return PixelStyleCreate(RESET, DEFAULT, WHITE);
}

void PixelMakeEmpty(Pixel *pixel) {
    PixelMake(pixel, RESET, BLACK, WHITE, 0);
}

void PixelMakeDefault(Pixel *pixel, wchar info) {
    PixelMakeEmpty(pixel);
    PixelInfo(*pixel) = info;
    PixelStyle(*pixel) = PixelStyleCreateDefault();
}

void PixelMake(Pixel* pixel, PixelAttribute attribute, PixelColor background, PixelColor foreground, wchar info) {
    PixelStyle(*pixel) = PixelStyleCreate(attribute, background, foreground);
    PixelInfo(*pixel) = info;
}

Pixel PixelCreateEmpty() {
    Pixel pixel;
    PixelMakeEmpty(&pixel);
    return pixel;
}

Pixel PixelCreateDefault(wchar info) {
    Pixel pixel;
    PixelMakeDefault(&pixel, info);
    return pixel;
}

Pixel PixelCreate(PixelAttribute attribute, PixelColor background, PixelColor foreground, wchar info) {
    Pixel pixel;
    PixelMake(&pixel, attribute, background, foreground, info);
    return pixel;
}

void PixelPrint(Pixel pixel) {
    if (PixelBackground(pixel) == DEFAULT) {
        wprintf(L"%c[%d;%dm", 0x1B, PixelAttribute(pixel),  PixelForeground(pixel) + 30);
        wprintf(L"%lc", PixelInfo(pixel) ? PixelInfo(pixel) : L' ');
        wprintf(L"%c[%d;%dm", 0x1B, RESET,  WHITE + 30);
    } else {
        wprintf(L"%c[%d;%d;%dm", 0x1B, PixelAttribute(pixel),  PixelForeground(pixel) + 30, PixelBackground(pixel) + 40);
        wprintf(L"%lc", PixelInfo(pixel) ? PixelInfo(pixel) : L' ');
        wprintf(L"%c[%d;%d;%dm", 0x1B, RESET,  WHITE + 30, BLACK + 40);
    }
}
