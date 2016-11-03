#include "graphics/terminal.h"
#include "boolean.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

uint TerminalGetActualWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

uint TerminalGetActualHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

uint TerminalGetWidth(Terminal terminal) {
    return terminal.width;
}

uint TerminalGetHeight(Terminal terminal) {
    return terminal.height;
}

TerminalBuffer TerminalGetBuffer(Terminal terminal) {
    return terminal.buffer;
}

void TerminalMake(Terminal* terminal, uint width, uint height) {
    setlocale(LC_ALL, "");
    terminal->width = width;
    terminal->height = height;

    terminal->buffer = (TerminalBuffer) malloc(width * height * sizeof(Pixel));
    TerminalClear(*terminal);
}

void TerminalMakeDefault(Terminal* terminal) {
    return TerminalMake(terminal, TerminalGetActualWidth(), TerminalGetActualHeight());
}

Terminal TerminalCreate(uint width, uint height) {
    Terminal terminal;
    TerminalMake(&terminal, width, height);
    return terminal;
}
Terminal TerminalCreateDefault() {
    Terminal terminal;
    TerminalMakeDefault(&terminal);
    return terminal;
}

Pixel TerminalGet(Terminal terminal, uint x, uint y) {
    TerminalBuffer buffer = TerminalGetBuffer(terminal);
    return buffer[y * TerminalGetWidth(terminal) + x];
}

void TerminalSet(Terminal terminal, uint x, uint y, Pixel pixel) {
    TerminalBuffer buffer = TerminalGetBuffer(terminal);
    buffer[y * TerminalGetWidth(terminal) + x] = pixel;
}

void TerminalClear(Terminal terminal) {
    TerminalBuffer buffer = TerminalGetBuffer(terminal);
    int i,j;
    for (i = 0; i < TerminalGetHeight(terminal); i++)
        for (j = 0; j < TerminalGetWidth(terminal); j++)
            buffer[i*TerminalGetWidth(terminal) + j] = PixelCreateDefault(0);
}

void TerminalRender(Terminal terminal) {
    system("clear");
    TerminalBuffer buffer = TerminalGetBuffer(terminal);
    int i,j;
    for (i = 0; i < TerminalGetHeight(terminal); i++) {
        for (j = 0; j < TerminalGetWidth(terminal); j++)
            PixelPrint(buffer[i*TerminalGetWidth(terminal) + j]);
        printf("\n");
    }
}

void TerminalDealoc(Terminal* terminal) {
    free (terminal->buffer);
}
