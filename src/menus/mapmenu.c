#include "menus/mapmenu.h"
#include "menus/menu_battle.h"
#include "graphics/ui.h"
#include "gamestate.h"
#include "map.h"

#include <stdlib.h>
#include <time.h>

String getCommand() {
    String result = StringCreate("");

    char k = (char) TerminalWaitKey();
    if (k == 0x1b) {
        char x = (char) TerminalWaitKey();
        char y = (char) TerminalWaitKey();
        if (x == 91)
            switch (y) {
                case 65 : StringAppendString(&result, StringCreate("GU")); break;
                case 68 : StringAppendString(&result, StringCreate("GL")); break;
                case 67 : StringAppendString(&result, StringCreate("GR")); break;
                case 66 : StringAppendString(&result, StringCreate("GD")); break;
            }
    } else {
        wprintf(L"%c", k);
        StringAppendChar(&result, k);
        String new = StringCreate("");
        StringReadln(&new);
        StringAppendString(&result, new);
    }

    return result;
}

MapNode* getRandomMap() {
    static uint id = 0;
    String mapFile[1];
    mapFile[0] = StringCreate("res/map1.map");

    srand(time(0));
    uint i = rand() % 1;

    Map* map = (Map*) malloc (sizeof (Map));
    MapMakeEmpty(map);
    MapFillFromFile(map, fopen(mapFile[i], "r"));

    MapNode* mn = (MapNode*) malloc(sizeof(MapNode));
    mn->map = *map;
    mn->id = ++id;
    mn->left = mn->right = mn->top = mn->bottom = NULL;

    return mn;
}

Enemy* getRandomEnemy() {
    String enemyFile[3];
    enemyFile[0] = StringCreate("res/enemy1.enemy");
    enemyFile[1] = StringCreate("res/enemy2.enemy");
    enemyFile[2] = StringCreate("res/enemy3.enemy");

    return LoadPlayerFromFile(enemyFile[rand()%3]);
}

void showMapMenuInformation(GameState *gameState) {
    TerminalClear(*(gameState->terminal));

    MapPutOnTerminal(gameState->currentMap->map, *(gameState->terminal),  TerminalGetCenterX(*(gameState->terminal), gameState->currentMap->map.width) , 2);
    UIDrawBoxLine(*gameState->terminal, TerminalGetCenterX(*gameState->terminal, gameState->currentMap->map.width) - 2, 1,
        2 * (gameState->currentMap->map.width) +4, gameState->currentMap->map.height+2,
        PixelStyleCreateDefault(), THICKLINE);

    UIDrawBox(*(gameState->terminal), 3, 3, 50, 5,
        PixelCreateDefault(0x250f), PixelCreateDefault(0x2513),
        PixelCreateDefault(0x251b), PixelCreateDefault(0x2517),
        PixelCreateDefault(0x2501), PixelCreateDefault(0x2503),
        PixelCreateDefault(0x2501), PixelCreateDefault(0x2503));
    UIDrawBox(*(gameState->terminal), 3, 7, 50, 17,
        PixelCreateDefault(0x2523), PixelCreateDefault(0x252b),
        PixelCreateDefault(0x251b), PixelCreateDefault(0x2517),
        PixelCreateDefault(0x2501), PixelCreateDefault(0x2503),
        PixelCreateDefault(0x2501), PixelCreateDefault(0x2503));

    UIDrawText(*(gameState->terminal), 20, 5, PixelStyleCreateDefault(), StringCreate("Player Information"));
    UIDrawVLine(*(gameState->terminal), 18, 7, 17, PixelCreateDefault(0x2533), PixelCreateDefault(0x253b), PixelCreateDefault(0x2503));

    UIDrawText(*(gameState->terminal), 5, 9, PixelStyleCreateDefault(), StringCreate("Player Name"));
    UIDrawText(*(gameState->terminal), 20, 9, PixelStyleCreateDefault(), StringCreate(gameState->player->name));
    UIDrawHLine(*(gameState->terminal), 3, 11, 50, PixelCreateDefault(0x2523), PixelCreateDefault(0x252b), PixelCreateDefault(0x2501));
    TerminalSet(*(gameState->terminal), 18, 11, PixelCreateDefault(0x254b));

    UIDrawText(*(gameState->terminal), 5, 13, PixelStyleCreateDefault(), StringCreate("Player HP"));
    UIDrawText(*(gameState->terminal), 20, 13, PixelStyleCreateDefault(), StringFromUint(gameState->player->HP));
    UIDrawHLine(*(gameState->terminal), 3, 15, 50, PixelCreateDefault(0x2523), PixelCreateDefault(0x252b), PixelCreateDefault(0x2501));
    TerminalSet(*(gameState->terminal), 18, 15, PixelCreateDefault(0x254b));

    UIDrawText(*(gameState->terminal), 5, 17, PixelStyleCreateDefault(), StringCreate("Player STR"));
    UIDrawText(*(gameState->terminal), 20, 17, PixelStyleCreateDefault(), StringFromUint(gameState->player->STR));
    UIDrawHLine(*(gameState->terminal), 3, 19, 50, PixelCreateDefault(0x2523), PixelCreateDefault(0x252b), PixelCreateDefault(0x2501));
    TerminalSet(*(gameState->terminal), 18, 19, PixelCreateDefault(0x254b));

    UIDrawText(*(gameState->terminal), 5, 21, PixelStyleCreateDefault(), StringCreate("Player DEF"));
    UIDrawText(*(gameState->terminal), 20, 21, PixelStyleCreateDefault(), StringFromUint(gameState->player->DEF));

    TerminalRender(*(gameState->terminal));
}

void MapMenuShow(GameState *gameState) {
    if (!gameState->currentMap) {
        gameState->currentMap = getRandomMap();
        gameState->nMap = 1;
        gameState->playerPosition = gameState->currentMap->map.startCenter;
    }
    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, MAP_PLAYER);

    String command = StringCreate("");
    boolean game_loop = true;
    uint beforeMove = MAP_FREE;
    while (game_loop) {
        showMapMenuInformation(gameState);

        command = getCommand();

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
        else if (StringEquals(command, StringCreate("SAVE")))
            GameStateSave(gameState);

        uint afterMove = MAP_FREE;
        beforeMove = MAP_FREE;
        if (move) {
            uint nx = gameState->playerPosition.x + mx;
            uint ny = gameState->playerPosition.y + my;
            if (nx > 0 && nx <= MapWidth(gameState->currentMap->map)
                && ny > 0 && ny <= MapHeight(gameState->currentMap->map)
                && MapGet(gameState->currentMap->map, nx, ny) != MAP_WALL) {
                afterMove = MapGet(gameState->currentMap->map, nx, ny);
                MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, beforeMove);
                MapSet(gameState->currentMap->map, nx, ny, MAP_PLAYER);
                gameState->playerPosition.x = nx;
                gameState->playerPosition.y = ny;
            }

            if (nx == 0) {
                if (gameState->currentMap->left == NULL && gameState->nMap < 25)
                    gameState->currentMap->left = getRandomMap();
                if (gameState->currentMap->left != NULL) {
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, beforeMove);
                    MapNode* tmp = gameState->currentMap;
                    gameState->currentMap = gameState->currentMap->left;
                    gameState->currentMap->right = tmp;
                    gameState->playerPosition = gameState->currentMap->map.startRight;
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, MAP_PLAYER);
                }
            } else if (ny == 0) {
                if (gameState->currentMap->top == NULL && gameState->nMap < 25)
                    gameState->currentMap->top = getRandomMap();
                if (gameState->currentMap->top != NULL) {
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, beforeMove);
                    MapNode* tmp = gameState->currentMap;
                    gameState->currentMap = gameState->currentMap->top;
                    gameState->currentMap->bottom = tmp;
                    gameState->playerPosition = gameState->currentMap->map.startBottom;
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, MAP_PLAYER);
                }
            } else if (ny > gameState->currentMap->map.height) {
                if (gameState->currentMap->bottom == NULL && gameState->nMap < 25)
                    gameState->currentMap->bottom = getRandomMap();
                if (gameState->currentMap->bottom != NULL) {
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, beforeMove);
                    MapNode* tmp = gameState->currentMap;
                    gameState->currentMap = gameState->currentMap->bottom;
                    gameState->currentMap->top = tmp;
                    gameState->playerPosition = gameState->currentMap->map.startTop;
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, MAP_PLAYER);
                }
            } else if (nx > gameState->currentMap->map.width) {
                if (gameState->currentMap->right == NULL && gameState->nMap < 25)
                    gameState->currentMap->right = getRandomMap();
                if (gameState->currentMap->right != NULL) {
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, beforeMove);
                    MapNode* tmp = gameState->currentMap;
                    gameState->currentMap = gameState->currentMap->right;
                    gameState->currentMap->left = tmp;
                    gameState->playerPosition = gameState->currentMap->map.startLeft;
                    MapSet(gameState->currentMap->map, gameState->playerPosition.x, gameState->playerPosition.y, MAP_PLAYER);
                }
            }

            beforeMove = MAP_FREE;
            if (afterMove == MAP_ENEMY) {
                Enemy* enemy = getRandomEnemy();
                int result = BattleMenuShow(gameState, enemy);
                if (result == 0) beforeMove = MAP_ENEMY;
            } else if (afterMove == MAP_HEAL)
                gameState->player->HP = min(gameState->player->MAXHP, gameState->player->MAXHP + 5 + rand()%5);

            if (gameState->player->HP <= 0)
                return;
        }
    }
}
