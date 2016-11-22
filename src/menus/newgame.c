#include "graphics/terminal.h"
#include "graphics/ui.h"

#include "menus/mainmenu.h"
#include "menus/newgame.h"
#include "gamestate.h"
#include "player.h"

void NewGameShow(GameState* gameState) {
    Terminal* terminal = gameState->terminal;
    TerminalClear(*terminal);

    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, 22, PixelStyleCreateDefault(), MULTILINE);

    /* Membaca file yang berisi logo game */
    FILE *file = fopen("res/brightsouls.img","r");
    Image mainmenuImage;
    if(file) {
        mainmenuImage = ImageCreateFromFile(file, PixelStyleCreateDefault());
        UIDrawImage(*terminal, TerminalGetCenterX(*terminal, ImageWidth(mainmenuImage)), 5, mainmenuImage);
        fclose(file);
    }

    /* Membaca file yang berisi username
    String username = StringCreate("");
    char CC;
    file = fopen("res/username", "r");
    fscanf(file, "%c", &CC);
    while(CC != '.'){
        StringAppendChar(&username, CC);
        fscanf(file, "%c", &CC);
    }
    fclose(file);
    */

    String str = StringCreate("Please enter your name:");
    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 8, PixelStyleCreateDefault(), str);

    TerminalRender(*terminal);

    /* Menuliskan username ke file eksternal */
    String name = StringCreate("");
    StringReadln(&name);
    if(StringSize(name) == 0) NewGameShow(gameState);
    else{
        gameState->player = PlayerNew(name);
        /*
        file = fopen("res/username", "w");
        fprintf(file, "%s.", name);
        fclose(file);
        */
    }
}
