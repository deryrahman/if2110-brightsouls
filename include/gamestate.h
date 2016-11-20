#ifndef _H_GAME_STATE
#define _H_GAME_STATE

#include "player.h"
#include "map.h"

typedef struct {
    Terminal* terminal;
    Player* player;
    Map* currentMap;
    Point playerPosition;
    uint nMap;
} GameState;

void GameStateDealoc(GameState* gamestate);

GameState* GameStateNew();

#endif
