#include "graphics/terminal.h"
#include "boolean.h"
#include "xstring.h"

#include <wchar.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <fcntl.h>
#include <time.h>

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

uint TerminalGetCenterX(Terminal terminal, uint width) {
    return (TerminalGetWidth(terminal) + 1 - width + 1) / 2 - 1;
}

uint TerminalGetCenterY(Terminal terminal, uint height) {
    return (TerminalGetHeight(terminal) + 1 - height + 1) / 2 - 1;
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
    if (x >= 0 && x < TerminalGetWidth(terminal) && y >= 0 && y < TerminalGetHeight(terminal) ) {
        TerminalBuffer buffer = TerminalGetBuffer(terminal);
        buffer[y * TerminalGetWidth(terminal) + x] = pixel;
    }
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
        wprintf(L"\n");
    }
}

void TerminalDealoc(Terminal* terminal) {
    free (terminal->buffer);
}

void TerminalDelay(uint milisec) {
    clock_t start = clock();
    clock_t finished = start + ((unsigned long long) milisec* (unsigned long long) CLOCKS_PER_SEC)/1000;
    while (clock() < finished);
}
