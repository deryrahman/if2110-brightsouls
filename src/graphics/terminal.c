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
#include <termios.h>

void TerminalClearScreen() {
    system("clear");
}

void TerminalGotoXY(uint x, uint y) {
    wprintf(L"%c[%d;%df", 0x1b, y, x);
}

int TerminalWaitKey() {
    struct termios savedState, newState;

    if (-1 == tcgetattr(STDIN_FILENO, &savedState)) return EOF;
    newState = savedState;

    newState.c_lflag &= ~(ECHO | ICANON);
    newState.c_cc[VMIN] = 1;

    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState)) return EOF;
    int h = getchar();
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState)) return EOF;

    return h;
}

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

    terminal->backBuffer = (TerminalBuffer) malloc(width * height * sizeof(Pixel));
    int i; for (i = 0; i < width * height; i++) terminal->backBuffer[i].info = 0;
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
        if (buffer[y * TerminalGetWidth(terminal) + x].info == ' ')
            buffer[y * TerminalGetWidth(terminal) + x].info = 0;
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
    TerminalBuffer buffer = TerminalGetBuffer(terminal);

    int i,j;
    for (i = 0; i < TerminalGetHeight(terminal); i++) {
        for (j = 0; j < TerminalGetWidth(terminal); j++) {
                Pixel new = buffer[i*TerminalGetWidth(terminal) + j];
                Pixel old = terminal.backBuffer[i*TerminalGetWidth(terminal) + j];
                if (new.info != old.info || new.style.foreground != old.style.foreground ||
                    new.style.background != old.style.background || new.style.attribute != old.style.attribute) {
                    TerminalGotoXY(j, i);
                    PixelPrint(new);
                }
            }
    }
    TerminalGotoXY(1,TerminalGetHeight(terminal)-1);
    for (i = 0; i < TerminalGetWidth(terminal); i++)
        PixelPrint(PixelCreateDefault(0));
    TerminalGotoXY(1,TerminalGetHeight(terminal)-1);

    for (i = 0; i < TerminalGetHeight(terminal); i++)
        for (j = 0; j < TerminalGetWidth(terminal); j++)
            terminal.backBuffer[i*TerminalGetWidth(terminal) + j] = buffer[i*TerminalGetWidth(terminal) + j];
}

void TerminalDealoc(Terminal* terminal) {
    free (terminal->buffer);
}

void TerminalDelay(uint milisec) {
    clock_t start = clock();
    clock_t finished = start + ((unsigned long long) milisec* (unsigned long long) CLOCKS_PER_SEC)/1000;
    while (clock() < finished);
}
