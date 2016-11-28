#include "gamestate.h"
#include "player.h"
#include "map.h"

int main() {
    GameState gameState;

    if (GameStateLoad(&gameState)) {
        printf("Player name\t: %s\n", gameState.player->name);
        printf("Player HP\t: %d/%d\n", gameState.player->HP, gameState.player->MAXHP);
        printf("Player ATTACK\t: %d\n", gameState.player->STR);
        printf("Player DEFENSE\t: %d\n", gameState.player->DEF);
        printf("Player ATTACK SKILL\t: %d\n", gameState.player->STRSKILL);
        printf("Player DEFENSE SKILL\t: %d\n", gameState.player->DEFSKILL);
        printf("Player LEVEL\t: %d\n", gameState.player->LVL);
        printf("Player EXP\t: %d\n", gameState.player->EXP);

        printf("\n\n%s\n", MapToString(*gameState.currentMap));
    }

    return 0;
}
