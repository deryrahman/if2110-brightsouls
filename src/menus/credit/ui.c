#include "graphics/ui.h"
#include "graphics/pixel.h"
#include "graphics/terminal.h"
#include "integer.h"

#include <stdio.h>
#include <stdlib.h>

void UIDrawBox(Terminal terminal, uint x, uint y, uint width, uint height, Pixel border1, Pixel border2, Pixel border3, Pixel border4, Pixel side1, Pixel side2, Pixel side3, Pixel side4) {
    TerminalSet(terminal, x, y, border1);
    TerminalSet(terminal, x + width - 1, y, border2);
    TerminalSet(terminal, x + width - 1, y + height - 1, border3);
    TerminalSet(terminal, x, y + height - 1, border4);

    int i;
    for (i = x + 1; i < x + width - 1; i++) {
        TerminalSet(terminal, i, y, side1);
        TerminalSet(terminal, i, y + height - 1, side3);
    }
    for (i = y + 1; i < y + height - 1; i++) {
        TerminalSet(terminal, x, i, side4);
        TerminalSet(terminal, x + width - 1, i, side2);
    }
}

void UIDrawBoxChar(Terminal terminal, uint x, uint y, uint width, uint height, Pixel character) {
    UIDrawBox(terminal, x, y, width, height, character, character, character, character, character, character, character, character);
}

void UIDrawBoxLine(Terminal terminal, uint x, uint y, uint width, uint height, PixelStyle style, LineBorder border) {
    Pixel border1,border2,border3,border4,side1,side2,side3,side4;
    PixelStyle(border1) = PixelStyle(border2) = PixelStyle(border3) = PixelStyle(border4) = PixelStyle(side1) = PixelStyle(side2) = PixelStyle(side3) = PixelStyle(side4) = style;
    switch (border) {
        case THINLINE:
            PixelInfo(border1) = 0x250c;
            PixelInfo(border2) = 0x2510;
            PixelInfo(border3) = 0x2518;
            PixelInfo(border4) = 0x2514;
            PixelInfo(side1) = PixelInfo(side3) = 0x2500;
            PixelInfo(side2) = PixelInfo(side4) = 0x2502;
            break;
        case THICKLINE:
            PixelInfo(border1) = 0x250f;
            PixelInfo(border2) = 0x2513;
            PixelInfo(border3) = 0x251b;
            PixelInfo(border4) = 0x2517;
            PixelInfo(side1) = PixelInfo(side3) = 0x2501;
            PixelInfo(side2) = PixelInfo(side4) = 0x2503;
            break;
        case MULTILINE:
            PixelInfo(border1) = 0x2554;
            PixelInfo(border2) = 0x2557;
            PixelInfo(border3) = 0x255d;
            PixelInfo(border4) = 0x255a;
            PixelInfo(side1) = PixelInfo(side3) = 0x2550;
            PixelInfo(side2) = PixelInfo(side4) = 0x2551;
            break;
        default:
            break;
    }

    UIDrawBox(terminal, x, y, width, height, border1, border2, border3, border4, side1, side2, side3, side4);
}

void UIDrawText(Terminal terminal, uint x, uint y, PixelStyle style, String str) {
    int i;
    Pixel pix = PixelCreateEmpty();
    PixelStyle(pix) = style;
    for (i = 0; i < StringLength(str); i++) {
        PixelInfo(pix) = str[i];
        if (x + i < TerminalGetWidth(terminal))
            TerminalSet(terminal, x + i, y, pix);
    }
}

void UIDrawElipsisText(Terminal terminal, uint x, uint y, uint maxChar, PixelStyle style, String str) {
    int i;
    Pixel pix = PixelCreateEmpty();
    PixelStyle(pix) = style;
    for (i = 0; i < max(maxChar,StringLength(str)); i++) {
        PixelInfo(pix) = str[i];
        if (x + i < TerminalGetWidth(terminal))
            TerminalSet(terminal, x + i, y, pix);
    }
    PixelInfo(pix) = 0x2026;
    if (StringLength(str) > maxChar)
        TerminalSet(terminal, x + maxChar - 1, y, pix);
}

void UIDrawMultilineText(Terminal terminal, uint x, uint y, uint width, PixelStyle style, String str, boolean wordWrap) {

}

void UIDrawImage(Terminal terminal, uint x, uint y, Image image) {
    uint i,j;
    for (i = 0; i < ImageHeight(image); i++)
        for (j = 0; j < ImageWidth(image); j++)
            TerminalSet(terminal, x + j, y + i, ImageInfo(image)[i][j]);
}
