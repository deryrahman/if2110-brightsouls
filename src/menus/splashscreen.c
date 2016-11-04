#include "graphics/terminal.h"
#include "graphics/ui.h"
#include "menus/splashscreen.h"

void SplashScreenShow(Terminal terminal) {
    UIDrawBoxLine(terminal, 1, 1, TerminalGetWidth(terminal) - 2, TerminalGetHeight(terminal) - 2, PixelStyleCreateDefault(), MULTILINE);

    FILE *file = fopen("/home/jauhararifin/Projects/brightsouls/res/brightsouls.img","r");
    if(file) {
        Image image = ImageCreateFromFile(file, PixelStyleCreateDefault());
        UIDrawImage(terminal, TerminalGetCenterX(terminal, ImageWidth(image)), TerminalGetCenterY(terminal, ImageHeight(image)), image);
        fclose(file);
    }

    TerminalRender(terminal);

    String str = StringStr(""); StringReadln(&str);
}
