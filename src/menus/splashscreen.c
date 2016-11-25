#include "player.h"
#include "xstring.h"
#include <stdio.h>
#include "menus/splashscreen.h"
#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/ui.h"
#include "xstring.h"
#include "menus/mainmenu.h"
#include "menus/newgame.h"
#include "gamestate.h"

void SplashScreenShow(GameState* gameState) {
    Terminal *terminal = gameState->terminal;
    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, TerminalGetHeight(*terminal) - 2, PixelStyleCreateDefault(), MULTILINE);

    FILE *file = fopen("res/brightsouls.img","r");
    if(file) {
        Image image = ImageCreateFromFile(file, PixelStyleCreateDefault());
        UIDrawImage(*terminal, TerminalGetCenterX(*terminal, ImageWidth(image)), TerminalGetCenterY(*terminal, ImageHeight(image)), image);
        fclose(file);
    }

    TerminalRender(*terminal);

    String str = StringCreate(""); StringReadln(&str);

    Terminal *terminalIns = gameState->terminal;
    TerminalClear(*terminalIns);
    UIDrawBoxLine(*terminalIns, 1, 1, TerminalGetWidth(*terminalIns) - 2, TerminalGetHeight(*terminalIns) - 2, PixelStyleCreateDefault(), MULTILINE);

    FILE *fileI = fopen("res/instruction.img","r");
    Image mainmenuImage;
    if(fileI) {
        mainmenuImage = ImageCreateFromFile(fileI, PixelStyleCreateDefault());
        UIDrawImage(*terminal, 4, 3, mainmenuImage);
        fclose(fileI);
    }
    str = StringCreate("Please do remember that every command that you type ends with enter.");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 6, PixelStyleCreateDefault(), str);

    str = StringCreate("In the menu screen you can choose to:");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 8, PixelStyleCreateDefault(), str);

    str = StringCreate("1. New Game, to select this please type 'New Game'");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 10, PixelStyleCreateDefault(), str);

    str = StringCreate("2. Start Game, to select this please type 'Start Game'");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 12, PixelStyleCreateDefault(), str);

    str = StringCreate("3. Load, to select this please type 'Load'");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 14, PixelStyleCreateDefault(), str);

    str = StringCreate("4. Exit, to select this please type 'Exit'");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 16, PixelStyleCreateDefault(), str);

    str = StringCreate("While you are looking for you enemy or medicine, you can press the up, down, left, or right button of the keyboard to move.");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 18, PixelStyleCreateDefault(), str);

    str = StringCreate("When you are in the battle mode, you can type 'A' to attack, 'B' to defense, or 'F' to flank.");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 20, PixelStyleCreateDefault(), str);

    str = StringCreate("Press enter to continue...");
    UIDrawText(*terminal,4, ImageHeight(mainmenuImage) + 22, PixelStyleCreateDefault(), str);

    TerminalRender(*terminal);
    str = StringCreate("");
    StringReadln(&str);
}
