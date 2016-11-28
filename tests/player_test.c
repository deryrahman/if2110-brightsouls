#include "player.h"
#include "tree.h"
#include "skill.h"
#include <stdio.h>

int main() {
    Player* player = LoadPlayerFromFile("savefile/player");
    Tree skill; SkillTreeDefault(&skill);
    LoadSkill(&skill, player->LVL);

    printf("%s %d %d %d %d %d %d\n", player->name, player->LVL, player->MAXHP, player->STR, player->DEF, player->STRSKILL, player->DEFSKILL);

    player->EXP = 100000;
    while (IsLevelUp(player)) {
        LevelUp(player);
        LoadSkill(&skill, player->LVL);
        printf("%s %d %d %d %d %d %d\n", player->name, player->LVL, player->MAXHP, player->STR, player->DEF, player->STRSKILL, player->DEFSKILL);
    }

    return 0;
}
