#include <stdio.h>
#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/ui.h"
#include "xstring.h"

#include "menus/mainmenu.h"
#include "menus/newgame.h"
#include "gamestate.h"

void MainMenuShow(GameState* gameState) {
    Terminal* terminal = gameState->terminal;
    TerminalClear(*terminal);

    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, TerminalGetHeight(*terminal) - 2, PixelStyleCreateDefault(), MULTILINE);

    /* Membaca file yang berisi logo game */
    FILE *file = fopen("res/brightsouls.img","r");
    Image mainmenuImage;
    if(file) {
        mainmenuImage = ImageCreateFromFile(file, PixelStyleCreateDefault());
        UIDrawImage(*terminal, TerminalGetCenterX(*terminal, ImageWidth(mainmenuImage)), 5, mainmenuImage);
        fclose(file);
    }

    /* Membaca file yang berisi username */
    String username = StringCreate("");
    char CC;
    file = fopen("res/username", "r");
    fscanf(file, "%c", &CC);
    while(CC != '.'){
        StringAppendChar(&username, CC);
        fscanf(file, "%c", &CC);
    }
    fclose(file);

    /* Tampilan akan berbeda antara dua kondisi: sudah ada username dan belum ada username */
    if(StringLength(username) > 0){
        String username_notif = StringCreate("Your username is:");
        String underline = StringCreate("----------------");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(username_notif)), ImageHeight(mainmenuImage) + 8, PixelStyleCreateDefault(), username_notif);
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(username)), ImageHeight(mainmenuImage) + 10, PixelStyleCreateDefault(), username);
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(underline)), ImageHeight(mainmenuImage) + 12, PixelStyleCreateDefault(), underline);

        String str = StringCreate("New Game");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreateDefault(), str);

        str = StringCreate("Start Game");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreateDefault(), str);

        str = StringCreate("Load");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreateDefault(), str);

        str = StringCreate("Exit");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 20, PixelStyleCreateDefault(), str);
    } else{
        String str = StringCreate("New Game");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 8, PixelStyleCreateDefault(), str);

        str = StringCreate("Start Game");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 10, PixelStyleCreateDefault(), str);

        str = StringCreate("Load");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 12, PixelStyleCreateDefault(), str);

        str = StringCreate("Exit");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreateDefault(), str);
    }

    TerminalRender(*terminal);

    /* Membaca menu */
    String menu = StringCreate("");
    StringReadln(&menu);
    if (StringEquals(menu, StringCreate("New Game"))) NewGameShow(gameState);
    else if (StringEquals(menu, StringCreate("Start Game"))) MainMenuShow(gameState);
    else if (StringEquals(menu, StringCreate("Load"))) MainMenuShow(gameState);
    else if (StringEquals(menu, StringCreate("Exit")));
    else MainMenuShow(gameState);
}
