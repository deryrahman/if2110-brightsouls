#include "tree.h"
#include "skill.h"
#include "player.h"
#include <stdio.h>

int main() {
    Tree skillTreeTest;

    SkillTreeDefault(&skillTreeTest);

    TreePrint(skillTreeTest, 0);
    TreePrintActivated(skillTreeTest, 0);

    int i;
    for (i = 1; i <= 50; i++) {
        printf("\n\n\n Level %d\n", i);
        LoadSkill(&skillTreeTest, i);
        TreePrintActivated(skillTreeTest, 0);
    }

    return 0;
}
