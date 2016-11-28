#include <stdio.h>
#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/ui.h"
#include "xstring.h"

#include "menus/mainmenu.h"
#include "menus/mapmenu.h"
#include "menus/newgame.h"
#include "gamestate.h"

int getMenuCommand() {
    char k = (char) TerminalWaitKey();
    if (k == 0x1b) {
        char x = (char) TerminalWaitKey();
        char y = (char) TerminalWaitKey();
        if (x == 91)
            switch (y) {
                case 65 : return 1;
                case 66 : return 2;
            }
    } else if (k == '\n')
        return 0;
    return -1;
}

int MainMenuShow(GameState* gameState) {
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

    /* Tampilan akan berbeda antara dua kondisi: sudah ada username dan belum ada username */

    String menus_item[4];
    int menus_item_num;
    int menu_item_first_y;
    int menu_item_selected = 0;

    if(gameState->player != NULL && gameState->player->name != NULL && StringLength(gameState->player->name) > 0){
        String username_notif = StringCreate("Your username is:");
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(username_notif)), ImageHeight(mainmenuImage) + 8, PixelStyleCreateDefault(), username_notif);
        UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(gameState->player->name)), ImageHeight(mainmenuImage) + 10, PixelStyleCreateDefault(), gameState->player->name);
        UIDrawHLine(*terminal, TerminalGetCenterX(*terminal, 20), ImageHeight(mainmenuImage) + 12, 20, PixelCreateDefault(0x2501),PixelCreateDefault(0x2501),PixelCreateDefault(0x2501));

        menus_item[0] = StringCreate("New Game");
        menus_item[1] = StringCreate("Start Game");
        menus_item[2] = StringCreate("Load");
        menus_item[3] = StringCreate("Exit");
        menus_item_num = 4;

        menu_item_first_y = ImageHeight(mainmenuImage) + 14;
    } else{
        menus_item[0] = StringCreate("New Game");
        menus_item[1] = StringCreate("Load");
        menus_item[2] = StringCreate("Exit");
        menus_item_num = 3;

        menu_item_first_y = ImageHeight(mainmenuImage) + 8;
    }

    int k = -1;
    do {
        if (k == 2) menu_item_selected++;
        if (k == 1) menu_item_selected--;
        menu_item_selected = (menu_item_selected + menus_item_num) % menus_item_num;
        uint i; for (i = 0; i < menus_item_num; i++) {
            PixelStyle style = PixelStyleCreateDefault();
            if (i == menu_item_selected)
                style = PixelStyleCreate(RESET, WHITE, BLACK);
            UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(menus_item[i])), menu_item_first_y + i * 2, style, menus_item[i]);
        }
        TerminalRender(*terminal);
        k = getMenuCommand();
    } while (k);

    /* Membaca menu */
    if (StringEquals(menus_item[menu_item_selected], StringCreate("New Game"))) return 1;
    else if (StringEquals(menus_item[menu_item_selected], StringCreate("Start Game"))) return 2;
    else if (StringEquals(menus_item[menu_item_selected], StringCreate("Load"))) return 3;
    else if (StringEquals(menus_item[menu_item_selected], StringCreate("Exit"))) return 4;
    else return 0;
}
