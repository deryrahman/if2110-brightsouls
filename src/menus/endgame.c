#include "menus/endgame.h"
#include "gamestate.h"
#include "player.h"
#include "xstring.h"
#include "graphics/terminal.h"
#include "graphics/ui.h"

void EndGameShow (GameState* gameState, boolean win) {
	Player* player = gameState->player;

	Terminal* terminal = gameState->terminal;
    TerminalClear(*terminal);

    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, TerminalGetHeight(*terminal) - 2, PixelStyleCreateDefault(), MULTILINE);

    if (!win) {
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
	 	UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreate(RESET, BLACK, GREEN), str);

		str = StringCreate("Your Defense : ");
		StringAppendString(&str,StringFromUint(player->DEF));
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreate(RESET,BLACK, BLUE), str);

	    str = StringCreate("Your Strength : ");
	    StringAppendString(&str,StringFromUint(player->STR));
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreate(RESET,BLACK, YELLOW), str);

	    str = StringCreate("YOU DA REAL MVP!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 20, PixelStyleCreate(RESET,BLACK, GREEN), str);

    	TerminalRender(*terminal);
		str = StringCreate("");
    	StringReadln(&str);


	    Terminal *terminalCre = gameState->terminal;
   		TerminalClear(*terminalCre);
    	UIDrawBoxLine(*terminalCre, 1, 1, TerminalGetWidth(*terminalCre) - 2, TerminalGetHeight(*terminalCre) - 2, PixelStyleCreateDefault(), MULTILINE);


	    FILE *fileCre = fopen("res/brightsouls.img","r");
	    if(fileCre) {
	        mainmenuImage = ImageCreateFromFile(fileCre, PixelStyleCreateDefault());
	        UIDrawImage(*terminalCre, TerminalGetCenterX(*terminalCre, ImageWidth(mainmenuImage)), 5, mainmenuImage);
	        fclose(fileCre);
	    }

	    str = StringCreate("Developed by Low-Profiled Team");
	    UIDrawText(*terminalCre,TerminalGetCenterX(*terminalCre, StringLength(str)), ImageHeight(mainmenuImage) + 8, PixelStyleCreateDefault(), str);

	    str = StringCreate("[Level Design]");
	    UIDrawText(*terminalCre,TerminalGetCenterX(*terminalCre, StringLength(str)), ImageHeight(mainmenuImage) + 12, PixelStyleCreateDefault(), str);

 		str = StringCreate("Iano");
	    UIDrawText(*terminalCre,TerminalGetCenterX(*terminalCre, StringLength(str)), ImageHeight(mainmenuImage) + 13, PixelStyleCreateDefault(), str);

 		str = StringCreate("Jauhar");
	    UIDrawText(*terminalCre,TerminalGetCenterX(*terminalCre, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreateDefault(), str);

 		str = StringCreate("[Storyline & Menu Design]");
	    UIDrawText(*terminalCre,TerminalGetCenterX(*terminalCre, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreateDefault(), str);

 		str = StringCreate("Yesa");
	    UIDrawText(*terminalCre,TerminalGetCenterX(*terminalCre, StringLength(str)), ImageHeight(mainmenuImage) + 17, PixelStyleCreateDefault(), str);

	    TerminalRender(*terminalCre);
		str = StringCreate("");
    	StringReadln(&str);

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

	    str = StringCreate("And of course you can do the reincarnation to play New Game!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreate(RESET,BLACK, YELLOW), str);

	    str = StringCreate("See you & better luck next time!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 20, PixelStyleCreate(RESET,BLACK, GREEN), str);
    }

    TerminalRender(*terminal);
    String str = StringCreate("");
    StringReadln(&str);

	FILE* save = fopen("savefile/username","w");
	if (save) fclose(save), remove("savefile/username");
	save = fopen("savefile/map","w");
	if (save) fclose(save), remove("savefile/map");
}
