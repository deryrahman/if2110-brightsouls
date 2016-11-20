#ifndef _H_MAP
#define _H_MAP

#include "point.h"
#include "graphics/terminal.h"
#include "integer.h"

#include <wchar.h>

extern const uint MAP_FREE;
extern const uint MAP_WALL;
extern const uint MAP_ENEMY;
extern const uint MAP_HEAL;
extern const uint MAP_PLAYER;

extern const wchar TERMINAL_FREE;
extern const wchar TERMINAL_WALL;
extern const wchar TERMINAL_ENEMY;
extern const wchar TERMINAL_HEAL;
extern const wchar TERMINAL_PLAYER;

typedef struct {
    uint width;
    uint height;
    uint *info;
    Point startRight;
    Point startTop;
    Point startLeft;
    Point startBottom;
    Point startCenter;
} Map;

typedef struct {
    Map map;
    Map *right;
    Map *left;
    Map *top;
    Map *bottom;
} MapNode;

uint MapWidth(Map map);
uint MapHeight(Map map);

void MapMakeEmpty(Map *map);
void MapMake(Map *map, uint width, uint height);

void MapFillFromFile(Map *map, FILE *file);

Map MapCreateEmpty();
Map MapCreate(uint width, uint height);

uint MapGet(Map map, uint x, uint y);
void MapSet(Map map, uint x, uint y, uint info);

void MapPutOnTerminal(Map map, Terminal terminal, uint x, uint y);

void MapDealoc(Map map);

#endif
