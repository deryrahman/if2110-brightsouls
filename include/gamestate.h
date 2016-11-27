#ifndef _H_GAME_STATE
#define _H_GAME_STATE

#include "player.h"
#include "map.h"
#include "tree.h"

typedef struct {
    Terminal* terminal;
    Player* player;
    MapNode* currentMap;
    Point playerPosition;
    uint nMap;
} GameState;

void GameStateDealoc(GameState* gamestate);

GameState* GameStateNew();

void GameStateSave(GameState* gameState);
boolean GameStateLoad(GameState* gameState);

#endif
