#include <stdio.h>
#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/ui.h"

int main (int argc, char const *argv[]) {

	Terminal* terminal = gameState->terminal;
    TerminalClear(*terminal);

    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, TerminalGetHeight(*terminal) - 2, PixelStyleCreateDefault(), MULTILINE);


 	String str = StringCreate("HP kamu : %d");
 	UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 14, PixelStyleCreateDefault(), str);
	
	str = StringCreate("Defense kamu : ");
    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 16, PixelStyleCreateDefault(), str);

    str = StringCreate("Strenth kamu : ");
    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 18, PixelStyleCreateDefault(), str);

    //if-else untuk menang kalahnya
    str = StringCreate("Selamat");
    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(str)), ImageHeight(mainmenuImage) + 20, PixelStyleCreateDefault(), str);


  return 0;
}

