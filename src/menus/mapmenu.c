#include "menus/mapmenu.h"
#include "gamestate.h"
#include "map.h"

#include <stdlib.h>
#include <time.h>

Map* getRandomMap() {
    String mapFile[1];
    mapFile[0] = StringCreate("res/map1.map");

    srand(time(0));
    uint i = rand() % 1;

    Map* map = (Map*) malloc (sizeof (Map));
    MapMakeEmpty(map);
    MapFillFromFile(map, fopen(mapFile[i], "r"));

    return map;
}

void MapMenuShow(GameState *gameState) {
    if (!gameState->currentMap) {
        gameState->currentMap = getRandomMap();
        gameState->nMap = 1;
        gameState->playerPosition = gameState->currentMap->startCenter;
    }
    MapSet(*gameState->currentMap, gameState->playerPosition.x, gameState->playerPosition.y, MAP_PLAYER);

    String command = StringCreate("");
    boolean game_loop = true;
    while (game_loop) {
        TerminalClear(*(gameState->terminal));
        MapPutOnTerminal(*gameState->currentMap, *(gameState->terminal),  TerminalGetCenterX(*(gameState->terminal), gameState->currentMap->width) , 2);
        TerminalRender(*(gameState->terminal));

        StringReadln(&command);

        boolean move = false;
        uint mx = 0;
        uint my = 0;
        if (StringEquals(command, StringCreate("GU")))
            move = true, mx = 0, my = -1;
        else if (StringEquals(command, StringCreate("GD")))
            move = true, mx = 0, my = 1;
        else if (StringEquals(command, StringCreate("GR")))
            move = true, mx = 1, my = 0;
        else if (StringEquals(command, StringCreate("GL")))
            move = true, mx = -1, my = 0;

        uint afterMove = MAP_FREE;
        if (move) {
            uint nx = gameState->playerPosition.x + mx;
            uint ny = gameState->playerPosition.y + my;
            if (nx > 0 && nx <= MapWidth(*gameState->currentMap)
                && ny > 0 && ny <= MapHeight(*gameState->currentMap)
                && MapGet(*gameState->currentMap, nx, ny) != MAP_WALL) {
                afterMove = MapGet(*gameState->currentMap, nx, ny);
                MapSet(*gameState->currentMap, gameState->playerPosition.x, gameState->playerPosition.y, MAP_FREE);
                MapSet(*gameState->currentMap, nx, ny, MAP_PLAYER);
                gameState->playerPosition = PointCreate(nx, ny);
            }

            if (afterMove == MAP_ENEMY);
            else if (afterMove == MAP_HEAL);
        }
    }
}
