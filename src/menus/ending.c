#include "menus/ending.h"
#include "gamestate.h"
#include "player.h"
#include "xstring.h"
#include "graphics/terminal.h"
#include "wchar.h"

void CreditShow (GameState* gameState) {
	Player* player = gameState->player;

	Terminal* terminal = gameState->terminal;
    TerminalClear(*terminal);

    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, TerminalGetHeight(*terminal) - 2, PixelStyleCreateDefault(), MULTILINE);

    if (player->HP > 0) {
	    /* Membaca file yang berisi text untuk kasus menang */
	    FILE *file = fopen("res/win.img","r");
	    Image mainmenuImage;
	    if(file) {
	        mainmenuImage = ImageCreateFromFile(file, PixelStyleCreateDefault());
	        UIDrawImage(*terminal, TerminalGetCenterX(*terminal, ImageWidth(mainmenuImage)), 5, mainmenuImage);
	        fclose(file);
	    }

	 	String str = StringCreate("Your HP : %d", );
	 	UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreateDefault(), str);
		
		str = StringCreate("Your Defense : %d", );
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreateDefault(), str);

	    str = StringCreate("Your Strength : %d", );
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreateDefault(), str);

	    str = StringCreate("We heard that you are a great player, so let's fight again!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreateDefault(), str);
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

	    str = StringCreate("We are so sorry that you are just bitten by our boss");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreateDefault(), str);

	    str = StringCreate("But of course you can do the reincarnation to play again!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreateDefault(), str);

	    str = StringCreate("See you & better luck next time!");
	    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreateDefault(), str);
    }

    str = StringCreate("");
    StringReadln(&str);
}

