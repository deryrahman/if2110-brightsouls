/* Driver */

#include "menus/menu_battle.h"
#include "graphics/terminal.h"
#include "graphics/ui.h"
#include "tree.h"
#include "player.h"
#include "gamestate.h"
#include "stackt.h"
#include "queue.h"
#include "xstring.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

Queue RandomAction();
void CetakQ(Queue Q);
Stack QueueToStack(Queue Q);
void Random2Number(int *irand);
void CommandCalculation(GameState* gameState, Enemy* enemy, int STR, int ESTR, int DEF, int EDEF, int *HP, int *EHP, int info);
void CommandHeader(GameState* gameState, Enemy* enemy, int *irand, Queue QMusuh, int round);
void CommandPanel(GameState* gameState, Enemy* enemy, int info);
void CommandInput(GameState* gameState, Enemy* enemy, Queue *QPlayer, QueueInfoType *Xq);
void CommandInputShow(GameState* gameState, Enemy* enemy, Queue QPlayer);
int CommandBattle(GameState* gameState, Enemy* enemy, Queue QPlayer, Queue QMusuh);
void CommandBox(GameState* gameState, Enemy* enemy, Queue QMusuh, Queue QPlayer, int *irand, int info, int round);

void BattleMenuShow (GameState* gameState, Enemy* enemy){
	Terminal* terminal = gameState->terminal;
	Player* player = gameState->player;
	int irand[2];
	Queue QPlayer;
	QueueInfoType Xq;
	int curr;
	int info=0;
	int ronde_max=10,ronde=1;
	Queue QMusuh;
	String cmd = StringCreate("");
	do{
		// Bikin queue pergerakan musuh
		QMusuh = RandomAction();
		// Ambil 2 elemen dalam stack secara random untuk hidden tampilan aksi musuh
		Random2Number(irand);
		// Bikin queue untuk input user
		QueueCreateEmpty(&QPlayer,4);
		info=0;
		while(!QueueIsFull(QPlayer)){
			CommandBox(gameState, enemy, QMusuh, QPlayer, irand, info, ronde);
			CommandInput(gameState, enemy, &QPlayer,&Xq);

			CommandBox(gameState, enemy, QMusuh, QPlayer, irand, info, ronde);
			wprintf(L"| 'E' to remove previous command or 'C' to continue... ");
			StringReadln(&cmd);
			while(cmd[0] != 'E' && cmd[0] != 'C'){
				wprintf(L"| WRONG INPUT! ");
				StringReadln(&cmd);
			}
			if(cmd[0]=='E'){
				QueueDelLast(&QPlayer,&Xq);
			} else if (cmd[0]=='C'){
				curr=QueueNBElmt(QPlayer)-1;

				// eksekusi hasil
				info=CommandBattle(gameState, enemy, QPlayer,QMusuh);

				//jika irand sama dengan NbElmt SPlayer, maka ubah nilainya
				irand[0]=(curr==irand[0])?4:irand[0];
				irand[1]=(curr==irand[1])?4:irand[1];
				CommandCalculation(gameState, enemy, player->STR+player->STRSKILL, enemy->STR, player->DEF+player->DEFSKILL, enemy->DEF, &(player->HP), &(enemy->HP), info);
			}
			if(player->HP<=0 || enemy->HP<=0)
				break;
		}
		CommandBox(gameState, enemy, QMusuh, QPlayer, irand, info, ronde);
		if(player->HP>0 && enemy->HP>0){
			wprintf(L"| 'C' to continue next battle... ");
			StringReadln(&cmd);
			while(cmd[0] != 'C'){
				wprintf(L"| WRONG INPUT! ");
				StringReadln(&cmd);
			}
		}
		if(player->HP<=0 || enemy->HP<=0)
			break;
		ronde++;
		QueueCreateEmpty(&QPlayer,4);
	} while (ronde<ronde_max && player->HP>0 && enemy->HP>0);
	// mengembalikan QMusuh jadi empty
	if(player->HP<=0){
		CommandBox(gameState, enemy, QMusuh, QPlayer, irand, 9, ronde);
	} else if (enemy->HP<=0){
		CommandBox(gameState, enemy, QMusuh, QPlayer, irand, 8, ronde);
	} else {
		CommandBox(gameState, enemy, QMusuh, QPlayer, irand, 10, ronde);
	}
}

Queue RandomAction(){
	Queue Q;
	QueueInfoType Xq;
	QueueCreateEmpty(&Q,4);
	srand(time(NULL));
	while(!QueueIsFull(Q)){
		int irand = (irand+rand()) % 3;
		if(irand==0)
			Xq='A';
		else if(irand==1)
			Xq='B';
		else
			Xq='F';
		QueueAdd(&Q,Xq);
	}
	return Q;
}

void CetakQ(Queue Q){
	while(!QueueIsEmpty(Q)){
		char Xq;
		QueueDel(&Q,&Xq);
		wprintf(L"%c", Xq);
	}
}

Stack QueueToStack(Queue Q){
	Stack S;
	StackInfoType Xs;
	StackCreateEmpty(&S);
	while(!QueueIsEmpty(Q)){
		QueueDel(&Q,&Xs);
		StackPush(&S,Xs);
	}
	return S;
}

void Random2Number(int *irand){
	srand(time(NULL));
	irand[0] = rand() % 4;
	srand(pow((time(NULL)%5),3));
	irand[1] = rand() % 4;
	while(irand[1]==irand[0]){
		irand[1] = rand() % 4;
	}
	if(irand[1]<irand[0]){
		int SwapTemp;
		SwapTemp=irand[1];
		irand[1]=irand[0];
		irand[0]=SwapTemp;
	}
}

void CommandHeader(GameState* gameState, Enemy* enemy, int *irand, Queue QMusuh, int round){
	Player* player = gameState->player;
	wprintf(L"|====================================================================================================     SKILL : \n");
	wprintf(L"| PLAYER : %s | LVL : %d | HP : %d | STR : %d | DEF : %d | Round : %d |\n", player->name, player->LVL, player->HP, player->STR, player->DEF, round);
	wprintf(L"|====================================================================================================     HP + %d | DEF + %d\n", player->STRSKILL, player->DEFSKILL);
	wprintf(L"| ENEMY : %s | HP : %d | Command : ", enemy->name, enemy->HP);

	int i=0;
	QueueInfoType Xq;
	while(i<4){
		QueueDel(&QMusuh,&Xq);
		if(irand[0]==i || irand[1]==i){
			wprintf(L"#");
		} else {
			wprintf(L"%c", Xq);
		}
		i++;
	}
	wprintf(L" |\n");
	wprintf(L"|====================================================================================================\n");
}
void CommandPanel(GameState* gameState, Enemy* enemy, int info){
	Player* player = gameState->player;
	wprintf(L"|\n| ");
	switch (info) {
		case 1 : wprintf(L"DRAW\n|"); break;
		case 2 : wprintf(L"PLAYER Attack! But it's blocked.\n| HP ENEMY : +%d", enemy->DEF/2); break;
		case 3 : wprintf(L"PLAYER Attack! It's very effective.\n| HP ENEMY : -%d",player->STR+player->STRSKILL); break;
		case 4 : wprintf(L"ENEMY Attack! But it's blocked.\n| HP PLAYER : +%d", (player->DEF+player->DEFSKILL)/2); break;
		case 5 : wprintf(L"ENEMY Flank! Bad decision dude.\n| HP PLAYER : -%d",enemy->STR*2); break;
		case 6 : wprintf(L"ENEMY Attack! Bad decision dude.\n| HP PLAYER : -%d",enemy->STR); break;
		case 7 : wprintf(L"USER Flank! It's very effective.\n| HP ENEMY : -%d",(player->STR+player->STRSKILL)*2); break;
		case 8 : wprintf(L"CONGRATULATION!\n| You Win!"); break;
		case 9 : wprintf(L"GAME OVER!\n| Please restart game, or load previous saved game"); break;
		case 10 : wprintf(L"DRAW!\n| Try again"); break;
		default : wprintf(L"PREPARE YOURSELF, ENEMY IS WATCHING YOU!\n| Please enter command.."); break;
	}
	wprintf(L"\n|\n|====================================================================================================\n");
}
void CommandInput(GameState* gameState, Enemy* enemy, Queue *QPlayer, QueueInfoType *Xq){
	String cmd = StringCreate("");
	wprintf(L"| ");
	StringReadln(&cmd);
	*Xq = cmd[0];
	while (*Xq!='A' && *Xq!='B' && *Xq!='F'){
		wprintf(L"| ");
		wprintf(L"WRONG INPUT! ");
		StringReadln(&cmd);
		*Xq = cmd[0];
	}
	QueueAdd(QPlayer,*Xq);
}
void CommandInputShow(GameState* gameState, Enemy* enemy, Queue QPlayer){
	int count=4;
	wprintf(L"| Inserted Commands : ");
	while(!QueueIsEmpty(QPlayer)){
		char Xq;
		QueueDel(&QPlayer,&Xq);
		wprintf(L"%c", Xq);
		count--;
	}
	while(count--){
		wprintf(L"_");
	}
}
int CommandBattle(GameState* gameState, Enemy* enemy, Queue QPlayer, Queue QMusuh){
	QueueInfoType X1,X2;
	while(!QueueIsEmpty(QPlayer) && QueueNBElmt(QPlayer)!=1){
		QueueDel(&QPlayer,&X1);
		QueueDel(&QMusuh,&X2);
	}
	QueueDel(&QPlayer,&X1);
	QueueDel(&QMusuh,&X2);

	if(X1==X2){
		return 1;
	} else if (X1=='A'){
		if(X2=='B'){
			return 2;
		} else {
			return 3;
		}
	} else if (X1=='B'){
		if(X2=='A'){
			return 4;
		} else {
			return 5;
		}
	} else if (X1=='F'){
		if(X2=='A'){
			return 6;
		} else {
			return 7;
		}
	}

	return 0;
}
void CommandBox(GameState* gameState, Enemy* enemy, Queue QMusuh, Queue QPlayer, int *irand, int info, int round){
	system("clear");
	CommandHeader(gameState, enemy, irand,QMusuh,round);
	CommandPanel(gameState, enemy, info);
	CommandInputShow(gameState, enemy, QPlayer);wprintf(L"\n");
}

void CommandCalculation(GameState* gameState, Enemy* enemy, int STR, int ESTR, int DEF, int EDEF, int *HP, int *EHP, int info){
	switch (info){
		case 2 : *EHP+=(EDEF/2); break;
		case 3 : *EHP-=(STR); break;
		case 4 : *HP+=(DEF/2); break;
		case 5 : *HP-=(ESTR*2); break;
		case 6 : *HP-=(ESTR); break;
		case 7 : *EHP-=(STR*2); break;
	}
	*EHP=(*EHP>enemy->MAXHP)?enemy->MAXHP:*EHP;
	*HP=(*HP>gameState->player->MAXHP)?gameState->player->MAXHP:*HP;
}
