#include "gamestate.h"
#include "graphics/terminal.h"
#include "player.h"
#include "map.h"
#include <stdlib.h>

void GameStateDealoc(GameState* gamestate) {
    TerminalDealoc(gamestate->terminal);
    free(gamestate);
}

GameState* GameStateNew(Terminal* terminal, Player* player, MapNode* mapNode) {
    GameState* gameState = (GameState*) malloc(sizeof(GameState));
    gameState->terminal = terminal;
    gameState->player = player;
    gameState->currentMap = mapNode;
    gameState->nMap = 0;
    return gameState;
}

void GameStateSave(GameState* gameState) {
    TulisStats("savefile/player", gameState->player);
    String mapSave = MapGraphToString(*gameState->currentMap);
    FILE *file = fopen("savefile/map","w");
    fprintf(file, "%s", mapSave);
    fclose(file);
}
