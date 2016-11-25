#include "menus/endgame.h"
#include "gamestate.h"
#include "player.h"
#include "xstring.h"
#include "graphics/terminal.h"
#include "graphics/ui.h"

void EndGameShow (GameState* gameState) {
	Player* player = gameState->player;

	Terminal* terminal = gameState->terminal;
    TerminalClear(*terminal);

    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, TerminalGetHeight(*terminal) - 2, PixelStyleCreateDefault(), MULTILINE);

    if ((player->HP) > 0) {
	    /* Membaca file yang berisi text untuk kasus menang */
	    FILE *file = fopen("res/win.img","r");
	    Image mainmenuImage;
	    if(file) {
	        mainmenuImage = ImageCreateFromFile(file, PixelStyleCreateDefault());
	        UIDrawImage(*terminal, TerminalGetCenterX(*terminal, ImageWidth(mainmenuImage)), 5, mainmenuImage);
	        fclose(file);
	    }

	 	String str = StringCreate("Your HP : ");
	 	StringAppendString(&str,StringFromUint(player->HP));
	 	UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreate(RESET,BLACK, GREEN), str);
		
		str = StringCreate("Your Defense : ");
		StringAppendString(&str,StringFromUint(player->DEF));
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreate(RESET,BLACK, BLUE), str);

	    str = StringCreate("Your Strength : ");
	    StringAppendString(&str,StringFromUint(player->STR));
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreate(RESET,BLACK, YELLOW), str);

	    str = StringCreate("We heard that you are a great player, so let's fight again!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 20, PixelStyleCreateDefault(RESET,BLACK, GREEN), str);
    }
    else {
	    /* Membaca file yang berisi text untuk kasus kalah */
	    FILE *file = fopen("res/lose.img","r");
	    Image mainmenuImage;
	    if(file) {
	        mainmenuImage = ImageCreateFromFile(file, PixelStyleCreateDefault());
	        UIDrawImage(*terminal, TerminalGetCenterX(*terminal, ImageWidth(mainmenuImage)), 5, mainmenuImage);
	        fclose(file);
	    }

	    String str = StringCreate("We are so sorry that you are just bitten by our boss");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreate(RESET,BLACK,GREEN), str);

	    str = StringCreate("We wish you have an even brighter soul");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreate(RESET,BLACK, BLUE), str);

	    str = StringCreate("And of course you can do the reincarnation to play again!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreate(RESET,BLACK, YELLOW), str);

	    str = StringCreate("See you & better luck next time!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 20, PixelStyleCreate(RESET,BLACK, GREEN), str);
    }

    TerminalRender(*terminal);
    String str = StringCreate("");
    StringReadln(&str);
}
