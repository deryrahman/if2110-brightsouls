#include <stdio.h>
#include <stdlib.h>

#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/ui.h"
#include "xstring.h"
#include "gamestate.h"

#include "menus/splashscreen.h"
#include "menus/mainmenu.h"

int main(int argc, char** argv){
	Terminal terminal = TerminalCreateDefault();
	GameState *gameState = GameStateNew(&terminal, NULL, NULL);

	SplashScreenShow(gameState);

	MainMenuShow(gameState);

	MapMenuShow(gameState);

	//UIDrawBoxLine(terminal, 11, 11, 30, 30, PixelStyleCreateDefault(), THINLINE);
	//UIDrawBoxLine(terminal, 41, 11, 30, 30, PixelStyleCreateDefault(), THICKLINE);
	//UIDrawBoxLine(terminal, 71, 11, 30, 30, PixelStyleCreateDefault(), MULTILINE);

	//UIDrawBoxChar(terminal, 101, 11, 30, 30, PixelCreate(RESET,RED,WHITE,L'#'));

	//UIDrawText(terminal, TerminalGetCenterX(terminal, StringLength(StringCreate("jauhar"))), 10, PixelStyleCreateDefault(), StringCreate("jauhar"));

	GameStateDealoc(gameState);

	return 0;
}
