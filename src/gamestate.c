#include "gamestate.h"
#include "graphics/terminal.h"
#include <stdlib.h>

void GameStateDealoc(GameState* gamestate) {
    TerminalDealoc(gamestate->terminal);
    free(gamestate);
}

GameState* GameStateNew(Terminal* terminal, Player* player, Map* map) {
    GameState* gameState = (GameState*) malloc(sizeof(GameState));
    gameState->terminal = terminal;
    gameState->player = player;
    gameState->currentMap = map;
    gameState->nMap = 0;
    return gameState;
}
