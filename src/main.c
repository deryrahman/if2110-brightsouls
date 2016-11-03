#include <stdio.h>
#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/ui.h"

int main(int argc, char** argv){
	Terminal terminal = TerminalCreateDefault();

	UIDrawBoxLine(terminal, 11, 11, 30, 30, PixelStyleCreateDefault(), THINLINE);
	UIDrawBoxLine(terminal, 41, 11, 30, 30, PixelStyleCreateDefault(), THICKLINE);
	UIDrawBoxLine(terminal, 71, 11, 30, 30, PixelStyleCreateDefault(), MULTILINE);
	UIDrawBoxChar(terminal, 101, 11, 30, 30, PixelCreate(RESET,RED,WHITE,L'#'));

	TerminalRender(terminal);

	TerminalDealoc(&terminal);
	return 0;
}
