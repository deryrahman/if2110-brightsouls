#ifndef _H_MENU_BATTLE
#define _H_MENU_BATTLE

#include "gamestate.h"
#include "player.h"
#include "stackt.h"
#include "queue.h"

int BattleMenuShow(GameState* gameState, Enemy* enemy, boolean BOSS);
/*
Queue RandomAction();
Stack QueueToStack(Queue Q);
void CetakQ(Queue Q);
void Random2Number(int *irand);
void CommandHeader(int *irand, Queue QMusuh,int round);
void CommandPanel(int info);
void CommandInputShow(Queue QPlayer);
void CommandInput(Queue *QPlayer, QueueInfoType *Xq);
int CommandBattle(Queue QPlayer, Queue QMusuh);
void CommandBox(Queue QMusuh, Queue QPlayer, int *irand, int info, int round);
void CommandCalculation(int STR, int ESTR, int DEF, int EDEF, int *HP, int *EHP, int info);
*/
#endif
