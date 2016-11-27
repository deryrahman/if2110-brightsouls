#include <stdio.h>
#include "menus/menu_skill.h"
#include "tree.h"
#include "graphics/terminal.h"
#include "graphics/pixel.h"
#include "graphics/ui.h"

void gotoxy(int x, int y){
		wprintf(L"%c[%d;%df", 0x1b, y, x);
}

void TulisStat(GameState *gameState, Tree P){
	uint left = TerminalGetCenterX(*gameState->terminal,0) - 25;
	uint top = TerminalGetCenterY(*gameState->terminal,0) + 5;

	UIDrawVLine(*(gameState->terminal), left-2,top - 1, 13, PixelCreateDefault(0x250f),PixelCreateDefault(0x2517),PixelCreateDefault(0x2503));
	UIDrawVLine(*(gameState->terminal), left+32,top - 1, 13, PixelCreateDefault(0x2513),PixelCreateDefault(0x251b),PixelCreateDefault(0x2503));

	UIDrawHLine(*(gameState->terminal), left-2,top - 1, 35, PixelCreateDefault(0x250f),PixelCreateDefault(0x2513),PixelCreateDefault(0x2501));
	UIDrawText(*(gameState->terminal), left + 9, top + 1, PixelStyleCreateDefault(), StringCreate("Skill Details"));
	UIDrawHLine(*(gameState->terminal), left-2,top + 3, 35, PixelCreateDefault(0x2523),PixelCreateDefault(0x252b),PixelCreateDefault(0x2501));

	UIDrawText(*(gameState->terminal), left, top + 4, PixelStyleCreateDefault(), StringCreate("Player`s MINIMUM EXP"));
	UIDrawText(*(gameState->terminal), left+30, top + 4, PixelStyleCreateDefault(), StringFromUint(TreeRoot(P).exp_req));
	UIDrawHLine(*(gameState->terminal), left-2,top + 5, 35, PixelCreateDefault(0x2523),PixelCreateDefault(0x252b),PixelCreateDefault(0x2501));

	UIDrawText(*(gameState->terminal), left, top + 6, PixelStyleCreateDefault(), StringCreate("Player`s ATTACK"));
	UIDrawText(*(gameState->terminal), left+30, top + 6, PixelStyleCreateDefault(), StringFromUint(TreeRoot(P).attack));
	UIDrawHLine(*(gameState->terminal), left-2,top + 7, 35, PixelCreateDefault(0x2523),PixelCreateDefault(0x252b),PixelCreateDefault(0x2501));

	UIDrawText(*(gameState->terminal), left, top + 8, PixelStyleCreateDefault(), StringCreate("Player`s DEFENCE"));
	UIDrawText(*(gameState->terminal), left+30, top + 8, PixelStyleCreateDefault(), StringFromUint(TreeRoot(P).deffense));
	UIDrawHLine(*(gameState->terminal), left-2,top + 9, 35, PixelCreateDefault(0x2523),PixelCreateDefault(0x252b),PixelCreateDefault(0x2501));

	FILE *file;
	if(TreeStatus(P)){
			UIDrawText(*(gameState->terminal), left, top + 10, PixelStyleCreateDefault(), StringCreate("You have acquired this skill"));
			file = fopen("res/yes.img","r");
	} else{
			UIDrawText(*(gameState->terminal), left, top + 10, PixelStyleCreateDefault(), StringCreate("You have not acquired this skill"));
			file = fopen("res/no.img","r");
	}
	UIDrawHLine(*(gameState->terminal), left-2,top + 11, 35, PixelCreateDefault(0x2517),PixelCreateDefault(0x251b),PixelCreateDefault(0x2501));

	/* Membaca file yang berisi tulisan YES or NO */
	Image mainmenuImage;
	if(file) {
			mainmenuImage = ImageCreateFromFile(file, PixelStyleCreateDefault());
			UIDrawImage(*(gameState->terminal), TerminalGetCenterX(*(gameState->terminal), ImageWidth(mainmenuImage))+22, 27, mainmenuImage);
			fclose(file);
	}
}

int getMenuCommandd() {
    char k = (char) TerminalWaitKey();
    if (k == 0x1b) {
        char x = (char) TerminalWaitKey();
        char y = (char) TerminalWaitKey();
        if (x == 91)
            switch (y) {
                case 65 : return 1;
                case 66 : return 2;
            }
    } else if (k == '\n')
        return 0;
    return -1;
}

void DrawTree(GameState *gameState, Tree P, int left, int top, int distance, boolean up, boolean right, int menu_item_selected){
		Terminal* terminal = gameState->terminal;
		if(up) left = TerminalGetCenterX(*terminal, 0);
		else if(right) left = left + distance;
		else left = left - distance;
		PixelStyle style;
		if(P == Nil);
		else if(TreeLeft(P) == Nil || TreeRight(P) == Nil){
				if (Urutan(TreeRoot(P)) == menu_item_selected) style = PixelStyleCreate(RESET, WHITE, BLACK); else style = PixelStyleCreateDefault();
				UIDrawText(*terminal, left, top, style, StringFromUint(TreeRoot(P).urutan));
				if(Urutan(TreeRoot(P)) == menu_item_selected) TulisStat(gameState, P);
		} else{
				if (Urutan(TreeRoot(P)) == menu_item_selected) style = PixelStyleCreate(RESET, WHITE, BLACK); else style = PixelStyleCreateDefault();
				UIDrawText(*terminal, left, top, style, StringFromUint(TreeRoot(P).urutan));
				UIDrawHLine(*terminal, left-(0.5*distance-1), top+5, distance-1, PixelCreateDefault(0x2501),PixelCreateDefault(0x2501),PixelCreateDefault(0x2501));
				UIDrawVLine(*terminal, left ,top+1, 5, PixelCreateDefault(0x2503),PixelCreateDefault(0x253b),PixelCreateDefault(0x2503));
				if(Urutan(TreeRoot(P)) == menu_item_selected) TulisStat(gameState, P);
				DrawTree(gameState, TreeLeft(P), left, top+5, 0.5*distance, false, false, menu_item_selected);
				DrawTree(gameState, TreeRight(P), left, top+5, 0.5*distance, false, true, menu_item_selected);
		}
}

void SkillMenuShow(GameState *gameState) {
	Terminal* terminal = gameState->terminal;
	Player* player = gameState->player;
	TerminalClear(*terminal);

	int menus_item_num;
	int menu_item_first_y;
	int menu_item_selected = 0;
	menus_item_num = 7;

	Tree root;
	LoadSkill(&root,player->EXP);

	UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, TerminalGetHeight(*terminal) - 2, PixelStyleCreateDefault(), MULTILINE);

	int k = -1;
	do {
			TerminalClear(*terminal);
			/* Membaca file yang berisi tulisan SKILLS */
			FILE *file = fopen("res/skills.img","r");
			Image mainmenuImage;
			if(file) {
					mainmenuImage = ImageCreateFromFile(file, PixelStyleCreateDefault());
					UIDrawImage(*terminal, TerminalGetCenterX(*terminal, ImageWidth(mainmenuImage)), 0, mainmenuImage);
					fclose(file);
			}

			if (k == 2) menu_item_selected++;
			if (k == 1) menu_item_selected--;
			menu_item_selected = (menu_item_selected + menus_item_num) % menus_item_num;
			DrawTree(gameState, root, 0, 11, 40, true, true, menu_item_selected);
			TerminalRender(*terminal);
			k = getMenuCommandd();
	} while (k);

	/*printf("\n");
	printf("SKILL :\n");
	TreePrint(root,0);printf("\n\n");
	printf("ACTIVATED SKILL :\n");
	TreePrintActivated(root,0);printf("\n");
	printf("TOTAL SKILL :\n");
	printf("++%u\n++%u\n", SkillTotalAttack(root), SkillTotalDeffense(root));*/

	TerminalRender(*terminal);
}
