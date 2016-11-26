#include "map.h"
#include "point.h"
#include "graphics/terminal.h"
#include "xstring.h"
#include "integer.h"
#include "listinteger.h"

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

const uint MAP_FREE = 0;
const uint MAP_WALL = 1;
const uint MAP_ENEMY = 2;
const uint MAP_HEAL = 3;
const uint MAP_PLAYER = 4;

const wchar TERMINAL_FREE = L'.';
const wchar TERMINAL_WALL = L'#';
const wchar TERMINAL_ENEMY = L'E';
const wchar TERMINAL_HEAL = L'M';
const wchar TERMINAL_PLAYER = L'P';

PixelStyle TERMINAL_FREE_PIXEL = {RESET,BLACK,BLACK};
PixelStyle TERMINAL_WALL_PIXEL = {RESET,WHITE,WHITE};
PixelStyle TERMINAL_ENEMY_PIXEL = {RESET,RED,BLACK};
PixelStyle TERMINAL_HEAL_PIXEL = {RESET,GREEN,BLACK};
PixelStyle TERMINAL_PLAYER_PIXEL = {RESET,YELLOW,BLACK};

uint MapWidth(Map map) {
    return map.width;
}

uint MapHeight(Map map) {
    return map.height;
}

void MapMakeEmpty(Map *map) {
    map->width = 0;
    map->height = 0;
    map->info = NULL;
    map->startRight = PointCreateEmpty();
    map->startTop = PointCreateEmpty();
    map->startLeft = PointCreateEmpty();
    map->startBottom = PointCreateEmpty();
}

void MapMake(Map *map, uint width, uint height) {
    map->width = width;
    map->height = height;
    map->info = (uint*) malloc(width*height*sizeof(uint));
}

void MapFillFromFile(Map *map, FILE *file) {
    if (file) {
        boolean bWidth = false;
        boolean bHeight = false;
        boolean bStartRight = false;
        boolean bStartTop = false;
        boolean bStartLeft = false;
        boolean bStartBottom = false;
        boolean bStartCenter = false;
        boolean allocated = false;

        String str = StringCreate("");
        uint y = 0;
        StringFreadln(&str, file);
        while (!feof(file)) {
            if (StringLength(str) == 0) {
                StringFreadln(&str, file);
                continue;
            }

            String key = StringCreate("");
            uint value = 0;
            uint value2 = 0;

            boolean spacedstring = true;

            uint i = 0;
            for (i = 0; i < StringLength(str) && str[i] != '='; i++)
                if (str[i] != ' ' && str[i] != '\t')
                    StringAppendChar(&key, str[i]), spacedstring = false;
            for (i++; i < StringLength(str) && str[i] < '0' && str[i] > '9'; i++)
                if (str[i] != ' ' && str[i] != '\t')
                    spacedstring = false;
            for (; i < StringLength(str) && str[i] >= '0' && str[i] <= '9'; i++)
                spacedstring = false, value = 10*value + (uint) (str[i]-'0');
            for (value2=0, i++; i < StringLength(str) && (str[i] < '0' || str[i] > '9'); i++);
            for (; i < StringLength(str) && str[i] >= '0' && str[i] <= '9'; i++)
                spacedstring = false, value2 = 10*value2 + (uint) (str[i] - '0');

            if (bWidth && bHeight && bStartRight && bStartTop && bStartLeft && bStartBottom && bStartCenter && !spacedstring) {
                y++;
                for (i = 0; i < StringLength(str); i++) {
                    uint x = MAP_FREE;

                    if (str[i] == (char) TERMINAL_WALL)
                        x = MAP_WALL;
                    else if (str[i] == (char) TERMINAL_HEAL)
                        x = MAP_HEAL;
                    else if (str[i] == (char) TERMINAL_ENEMY)
                        x = MAP_ENEMY;
                    else if (str[i] == (char) TERMINAL_PLAYER)
                        x = MAP_PLAYER;

                    MapSet(*map, i+1, y, x);
                }
                if (y >= map->height)
                    break;
            }

            if (StringEquals(key, StringCreate("width")))
                bWidth = true, map->width = value;
            else if (StringEquals(key, StringCreate("height")))
                bHeight = true, map->height = value;
            else if (StringEquals(key, StringCreate("startRight")))
                bStartRight = true, map->startRight = PointCreate(0,value);
            else if (StringEquals(key, StringCreate("startTop")))
                bStartTop = true, map->startTop = PointCreate(value,0);
            else if (StringEquals(key, StringCreate("startLeft")))
                bStartLeft = true, map->startLeft = PointCreate(0,value);
            else if (StringEquals(key, StringCreate("startBottom")))
                bStartBottom = true, map->startBottom = PointCreate(value,0);
            else if (StringEquals(key, StringCreate("startCenter")))
                bStartCenter = true, map->startCenter = PointCreate(value,value2);

            if (bWidth && bHeight && !allocated)
                allocated = true, MapMake(map, map->width, map->height);

            StringFreadln(&str, file);
        }

        (map->startTop).y = 1;
        (map->startRight).x = map->width;
        (map->startBottom).y = map->height; (map->startBottom).x = map->width - (map->startBottom).x;
        (map->startLeft).x = 1; (map->startLeft).y = map->height - (map->startLeft).y;
    }
}

MapNode* MapLoadNodeFromFile(String filename, uint *count) {
    MapNode* arr = (MapNode*) malloc(26 * sizeof(MapNode));
    int i; for (i = 0; i < 26; i++) arr[i].left = arr[i].right = arr[i].top = arr[i].bottom = NULL;
    FILE* file = fopen(filename, "r");

    if (!file)
        return NULL;

    uint ret_id = 0;
    while (!feof(file)) {
        Map m = MapCreateEmpty();
        MapFillFromFile(&m, file);
        if (count != NULL) *count += 1;
        String str = StringCreate("");

        StringFreadln(&str, file);
        uint id = 0;
        uint val = 0;
        while (StringLength(str) > 0) {
            String key = StringCreate("");
            String value = StringCreate("");

            int i = 0; for (;str[i] == ' ' || str[i] == '\t';i++);
            for (;i < StringLength(str) && str[i] != ' ' && str[i] != '\t' && str[i] != '=';i++) StringAppendChar(&key, str[i]);
            for (;str[i] == ' ' || str[i] == '\t' || str[i] == '=';i++);
            for (;i < StringLength(str) && str[i] != ' ' && str[i] != '\t' && str[i] != '=';i++) StringAppendChar(&value, str[i]);

            val = StringToUint(value);

            if (StringEquals(key, StringCreate("id"))) {
                id = val;
                arr[val].id = id;
                arr[val].map = m;
                if (ret_id == 0)
                    ret_id = id;
            }else if (StringEquals(key, StringCreate("left")))
                arr[id].left = &arr[val], arr[val].right = &arr[id];
            else if (StringEquals(key, StringCreate("right")))
                arr[id].right = &arr[val], arr[val].left = &arr[id];
            else if (StringEquals(key, StringCreate("top")))
                arr[id].top = &arr[val], arr[val].bottom = &arr[id];
            else if (StringEquals(key, StringCreate("bottom")))
                arr[id].bottom = &arr[val], arr[val].top = &arr[id];

            StringFreadln(&str, file);
        }
    }
    return (&arr[ret_id]);
}

String MapToString(MapNode map) {
    String str = StringCreate("");
    StringAppendString(&str, StringCreate("width="));
    StringAppendString(&str, StringFromUint(map.map.width));
    StringAppendChar(&str, '\n');

    StringAppendString(&str, StringCreate("height="));
    StringAppendString(&str, StringFromUint(map.map.height));
    StringAppendChar(&str, '\n');

    StringAppendString(&str, StringCreate("startRight="));
    StringAppendString(&str, StringFromUint(map.map.startRight.y));
    StringAppendChar(&str, '\n');

    StringAppendString(&str, StringCreate("startBottom="));
    StringAppendString(&str, StringFromUint(map.map.width - map.map.startBottom.x));
    StringAppendChar(&str, '\n');

    StringAppendString(&str, StringCreate("startLeft="));
    StringAppendString(&str, StringFromUint(map.map.height - map.map.startLeft.y));
    StringAppendChar(&str, '\n');

    StringAppendString(&str, StringCreate("startTop="));
    StringAppendString(&str, StringFromUint(map.map.startTop.x));
    StringAppendChar(&str, '\n');

    StringAppendString(&str, StringCreate("startCenter="));
    StringAppendString(&str, StringFromUint(map.map.startCenter.x));
    StringAppendChar(&str, ',');
    StringAppendString(&str, StringFromUint(map.map.startCenter.y));
    StringAppendChar(&str, '\n');

    uint i;
    for (i = 0; i < map.map.height; i++) {
        uint j;
        for (j = 0; j < map.map.width; j++) {
            wchar w = L' ';
            if (MapGet(map.map, j+1, i+1) == MAP_FREE)
                w = TERMINAL_FREE;
            else if (MapGet(map.map, j+1, i+1) == MAP_WALL)
                w = TERMINAL_WALL;
            else if (MapGet(map.map, j+1, i+1) == MAP_ENEMY)
                w = TERMINAL_ENEMY;
            else if (MapGet(map.map, j+1, i+1) == MAP_HEAL)
                w = TERMINAL_HEAL;
            else if (MapGet(map.map, j+1, i+1) == MAP_PLAYER)
                w = TERMINAL_PLAYER;
            StringAppendChar(&str, w);
        }
        StringAppendChar(&str,'\n');
    }

    StringAppendString(&str, StringCreate(".\nid="));
    StringAppendString(&str, StringFromUint(map.id));
    StringAppendChar(&str, '\n');

    if (map.left != NULL)
        StringAppendString(&str, StringCreate("left=")), StringAppendString(&str, StringFromUint(map.left->id)), StringAppendChar(&str, '\n');
    if (map.right != NULL)
        StringAppendString(&str, StringCreate("right=")), StringAppendString(&str, StringFromUint(map.right->id)), StringAppendChar(&str, '\n');
    if (map.top != NULL)
        StringAppendString(&str, StringCreate("top=")), StringAppendString(&str, StringFromUint(map.top->id)), StringAppendChar(&str, '\n');
    if (map.bottom != NULL)
        StringAppendString(&str, StringCreate("bottom=")), StringAppendString(&str, StringFromUint(map.bottom->id)), StringAppendChar(&str, '\n');

    StringAppendChar(&str, '\n');

    return str;
}

String MapGraphToStringRec(MapNode map, ListInteger* visited) {
    if (LISearch(*visited, map.id))
        return StringCreate("");

    String str = MapToString(map);
    LIInsVFirst(visited, map.id);

    if (map.top != NULL) {
        StringAppendString(&str, MapGraphToStringRec(*(map.top), visited));
    } if (map.right != NULL) {
        StringAppendString(&str, MapGraphToStringRec(*(map.right), visited));
    } if (map.bottom != NULL) {
        StringAppendString(&str, MapGraphToStringRec(*(map.bottom), visited));
    } if (map.left != NULL) {
        StringAppendString(&str, MapGraphToStringRec(*(map.left), visited));
    }

    return str;
}

String MapGraphToString(MapNode map) {
    ListInteger memo;
    LICreateEmpty(&memo);
    return MapGraphToStringRec(map, &memo);
}

Map MapCreateEmpty() {
    Map map;
    MapMakeEmpty(&map);
    return map;
}

Map MapCreate(uint width, uint height) {
    Map map;
    MapMake(&map, width, height);
    return map;
}

uint MapGet(Map map, uint x, uint y) {
    x--; y--;
    if (x >= 0 && x < map.width && y >= 0 && y < map.height)
        return map.info[y * map.width + x];
    return -1;
}
void MapSet(Map map, uint x, uint y, uint info) {
    x--; y--;
    if (x >= 0 && x < map.width && y >= 0 && y < map.height)
        map.info[y * map.width + x] = info;
}

void MapPutOnTerminal(Map map, Terminal terminal, uint x, uint y) {
    uint i;
    for (i = 0; i < map.height; i++) {
        uint j;
        for (j = 0; j < map.width; j++) {
            wchar w = L' ';
            PixelStyle s;
            if (MapGet(map, j+1, i+1) == MAP_FREE)
                w = TERMINAL_FREE, s = TERMINAL_FREE_PIXEL;
            else if (MapGet(map, j+1, i+1) == MAP_WALL)
                w = TERMINAL_WALL, s = TERMINAL_WALL_PIXEL;
            else if (MapGet(map, j+1, i+1) == MAP_ENEMY)
                w = TERMINAL_ENEMY, s = TERMINAL_ENEMY_PIXEL;
            else if (MapGet(map, j+1, i+1) == MAP_HEAL)
                w = TERMINAL_HEAL, s = TERMINAL_HEAL_PIXEL;
            else if (MapGet(map, j+1, i+1) == MAP_PLAYER)
                w = TERMINAL_PLAYER, s = TERMINAL_PLAYER_PIXEL;

            Pixel p = PixelCreateDefault(w);
            p.style = s;
            TerminalSet(terminal, x + j*2, y + i, p);
            //if (w == TERMINAL_FREE || w == TERMINAL_WALL)
                TerminalSet(terminal, x + j*2 + 1, y + i, p);
        }
    }
}

void MapDealoc(Map map) {
    free(map.info);
    MapMakeEmpty(&map);
}
