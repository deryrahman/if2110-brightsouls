#include "menus/endgame.h"
#include "gamestate.h"
#include "player.h"
#include "xstring.h"
#include "graphics/terminal.h"
#include "wchar.h"

void EndGameShow(GameState* gameState) {
    // Terminal* terminal = gameState->terminal;
    Player* player = gameState->player;
    if (player->HP <= 0)
        wprintf(L"KALAH\n");
    else
        wprintf(L"MENANG\n");
    String tmp = StringCreate("");
    StringReadln(&tmp);
}
