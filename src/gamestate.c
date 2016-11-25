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
    fprintf(file, "%s.", mapSave);
    fclose(file);
}

boolean GameStateLoad(GameState* gameState) {
    gameState->player = LoadPlayerFromFile("savefile/player");
    gameState->currentMap = MapLoadNodeFromFile("savefile/map");

    if (gameState->player == NULL || gameState->currentMap == NULL) {
        gameState->player = NULL;
        gameState->currentMap = NULL;
        return false;
    }

    Map map = gameState->currentMap->map;
    int i,j;
    boolean found = false;
    for (i = 1; !found && i <= map.height; i++)
        for (j = 1; !found && j <= map.width; j++)
            if (MapGet(map,j,i) == MAP_PLAYER) {
                gameState->playerPosition.x = j;
                gameState->playerPosition.y = i;
                found = true;
            }

    return true;
}
