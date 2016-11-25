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
void CommandInput(GameState* gameState, Enemy* enemy, Queue *QPlayer, QueueInfoType *Xq);
String CommandInputShow(Queue QPlayer);
int CommandBattle(Queue QPlayer, Queue QMusuh);
String EnemyCMD(int *irand, Queue QMusuh);
void CommandDisplay(GameState* gameState,Queue QPlayer, Queue QMusuh,int info,int *irand, uint ronde, Enemy* enemy);

int BattleMenuShow (GameState* gameState, Enemy* enemy){
	Player* player = gameState->player;
	
	QueueInfoType Xq;
	Queue QPlayer;
	Queue QMusuh;
	int irand[2];
	int info=0;
	uint ronde_max=10,ronde=1;
	String str = StringCreate("");
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
		    CommandDisplay(gameState, QPlayer, QMusuh, info, irand, ronde, enemy);
			StringReadln(&str);
			while (str[0]!='A' && str[0]!='B' && str[0]!='F'){
		    	CommandDisplay(gameState, QPlayer, QMusuh, 15, irand, ronde, enemy);
				StringReadln(&str);
			}
			QueueAdd(&QPlayer,str[0]);
		    CommandDisplay(gameState, QPlayer, QMusuh, 12, irand, ronde, enemy);
			StringReadln(&cmd);
			while(cmd[0] != 'E' && cmd[0] != '\0'){
				CommandDisplay(gameState, QPlayer, QMusuh, 13, irand, ronde, enemy);
				StringReadln(&cmd);
			}
			if(cmd[0]=='E'){
				QueueDelLast(&QPlayer,&Xq);
				info=14;
			} else {
				int curr=QueueNBElmt(QPlayer)-1;

				// eksekusi hasil
				info=CommandBattle(QPlayer,QMusuh);

				//jika irand sama dengan NbElmt SPlayer, maka ubah nilainya
				irand[0]=(curr==irand[0])?4:irand[0];
				irand[1]=(curr==irand[1])?4:irand[1];

				CommandCalculation(gameState, enemy, player->STR+player->STRSKILL, enemy->STR, player->DEF+player->DEFSKILL, enemy->DEF, &(player->HP), &(enemy->HP), info);
			}
			if(player->HP<=0 || enemy->HP<=0)
				break;
		}
		ronde++;
		if(player->HP<=0 || enemy->HP<=0){
			break;
		} else {
			CommandDisplay(gameState, QPlayer, QMusuh, info, irand, ronde, enemy);
			StringReadln(&str);
		}
	} while (ronde<ronde_max && player->HP>0 && enemy->HP>0);

	int hasil = 0; // 0 draw, 1 menang, -1 kalah
	if(player->HP<=0){
		hasil = -1;
		CommandDisplay(gameState, QPlayer, QMusuh, 9, irand, ronde, enemy);
	} else if (enemy->HP<=0){
		hasil = 1;
		CommandDisplay(gameState, QPlayer, QMusuh, 8, irand, ronde, enemy);
	} else {
		CommandDisplay(gameState, QPlayer, QMusuh, 10, irand, ronde, enemy);
	}
	StringReadln(&str);
 
	return hasil;
}


void CommandDisplay(GameState* gameState,Queue QPlayer, Queue QMusuh,int info,int *irand, uint ronde, Enemy* enemy){
	Terminal* terminal = gameState->terminal;
	Player* player = gameState->player;
	TerminalClear(*terminal);

		    String attributePlayer=StringCreate("PLAYER : ");
		    StringAppendString(&attributePlayer,player->name);
		    String attLVL=StringCreate(" | LVL : ");
		    StringAppendString(&attributePlayer,attLVL);
		    StringAppendString(&attributePlayer,StringFromUint(player->LVL));
		    String attHP=StringCreate(" | HP : ");
		    StringAppendString(&attributePlayer,attHP);
		    StringAppendString(&attributePlayer,StringFromUint((uint) player->HP));
		    String attSTR=StringCreate(" | STR : ");
		    StringAppendString(&attributePlayer,attSTR);
		    StringAppendString(&attributePlayer,StringFromUint(player->STR));
		    String attDEF=StringCreate(" | DEF : ");
		    StringAppendString(&attributePlayer,attDEF);
		    StringAppendString(&attributePlayer,StringFromUint(player->DEF));
		    String attROUND=StringCreate(" | Round : ");
		    StringAppendString(&attributePlayer,attROUND);
		    StringAppendString(&attributePlayer,StringFromUint(ronde));

		    String attributeEnemy=StringCreate("ENEMY : ");
		    StringAppendString(&attributeEnemy,enemy->name);
		    attHP=StringCreate(" | HP : ");
		    StringAppendString(&attributeEnemy,attHP);
		    StringAppendString(&attributeEnemy,StringFromUint((uint) enemy->HP));
		    String attCMD=StringCreate(" | Command : ");
		    StringAppendString(&attributeEnemy,attCMD);
		    StringAppendString(&attributeEnemy,EnemyCMD(irand,QMusuh));

		    // header
		    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, 3, PixelStyleCreateDefault(), MULTILINE);
		    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(attributePlayer)), 2, PixelStyleCreateDefault(), attributePlayer);

		    UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, 5, PixelStyleCreateDefault(), MULTILINE);
		    UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(attributeEnemy)), 4, PixelStyleCreateDefault(), attributeEnemy);

		    // panel
		    String line1,line2;
		    switch (info) {
				case 1 : line1=StringCreate("DRAW"); line2=StringCreate(""); break;
				case 2 : line1=StringCreate("PLAYER Attack! But it's blocked."); line2=StringCreate("HP ENEMY : +"); StringAppendString(&line2,StringFromUint(enemy->DEF/2)); break;
				case 3 : line1=StringCreate("PLAYER Attack! It's very effective."); line2=StringCreate("HP ENEMY : -"); StringAppendString(&line2,StringFromUint(player->STR+player->STRSKILL)); break;
				case 4 : line1=StringCreate("ENEMY Attack! But it's blocked."); line2=StringCreate("HP PLAYER : +"); StringAppendString(&line2,StringFromUint((player->DEF+player->DEFSKILL)/2)); break;
				case 5 : line1=StringCreate("ENEMY Flank! Bad decision dude."); line2=StringCreate("HP PLAYER : -"); StringAppendString(&line2,StringFromUint(enemy->STR*2)); break;
				case 6 : line1=StringCreate("ENEMY Attack! Bad decision dude."); line2=StringCreate("HP PLAYER : -"); StringAppendString(&line2,StringFromUint(enemy->STR*2));break;
				case 7 : line1=StringCreate("USER Flank! It's very effective."); line2=StringCreate("HP ENEMY : -"); StringAppendString(&line2,StringFromUint((player->STR+player->STRSKILL)*2)); break;
				case 8 : line1=StringCreate("CONGRATULATION!"); line2=StringCreate("You Win!"); break;
				case 9 : line1=StringCreate("GAME OVER!"); line2=StringCreate("Please restart game, or load previous saved game");break;
				case 10 : line1=StringCreate("DRAW!"); line2=StringCreate("Try again"); break;
				case 11 : line1=StringCreate("NEXT ROUND!"); line2=StringCreate(""); break;
				case 12 : line1=StringCreate("Press 'E' to remove previous command or"); line2=StringCreate("press anykey to continue.."); break;
				case 13 : line1=StringCreate("WRONG INPUT!"); line2=StringCreate("Press 'E' to remove previous command or press anykey to continue.."); break;
				case 14 : line1=StringCreate("Remove last command"); line2=StringCreate(""); break;
				case 15 : line1=StringCreate("WRONG INPUT!"); line2=StringCreate("Available action A, B, F"); break;
				default : line1=StringCreate("PREPARE YOURSELF, ENEMY IS WATCHING YOU!"); line2=StringCreate("Please insert command.."); break;
			}
			
			if(QueueIsFull(QPlayer) && info!=12 && info!=13){
		    	UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, 13, PixelStyleCreateDefault(), MULTILINE);
				UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(line1)), 7, PixelStyleCreateDefault(), line1);
				UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(line2)), 9, PixelStyleCreateDefault(), line2);
				String line3;
				if(info==8 || info==9 || info==10){
					line3=StringCreate("Press any key to continue..");
				} else {
					line3=StringCreate("NEXT ROUND! Press any key to continue..");
				}
				UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(line3)), 11, PixelStyleCreateDefault(), line3);
		    	UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, 15, PixelStyleCreateDefault(), MULTILINE);
				UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(CommandInputShow(QPlayer))), 14, PixelStyleCreateDefault(), CommandInputShow(QPlayer));
			} else {
		    	UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, 11, PixelStyleCreateDefault(), MULTILINE);
				UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(line1)), 7, PixelStyleCreateDefault(), line1);
				UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(line2)), 9, PixelStyleCreateDefault(), line2);
		    	UIDrawBoxLine(*terminal, 1, 1, TerminalGetWidth(*terminal) - 2, 13, PixelStyleCreateDefault(), MULTILINE);
				UIDrawText(*terminal,TerminalGetCenterX(*terminal, StringLength(CommandInputShow(QPlayer))), 12, PixelStyleCreateDefault(), CommandInputShow(QPlayer));
			}

		    TerminalRender(*terminal);
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
String EnemyCMD(int *irand, Queue QMusuh){
	String str=StringCreate("");
	int i=0;
	QueueInfoType Xq;
	while(i<4){
		QueueDel(&QMusuh,&Xq);
		if(irand[0]==i || irand[1]==i){
			StringAppendChar(&str,'#');
		} else {
			StringAppendChar(&str,Xq);
		}
		i++;
	}
	return str;
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
String CommandInputShow(Queue QPlayer){
	String str=StringCreate("Inserted Commands : ");
	int count=4;
	while(!QueueIsEmpty(QPlayer)){
		char Xq;
		QueueDel(&QPlayer,&Xq);
		StringAppendChar(&str,Xq);
		count--;
	}
	while(count--){
		StringAppendChar(&str,'_');
	}
	return str;
}
int CommandBattle(Queue QPlayer, Queue QMusuh){
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
// void CommandBox(GameState* gameState, Enemy* enemy, Queue QMusuh, Queue QPlayer, int *irand, int info, int round){
// 	system("clear");
// 	CommandHeader(gameState, enemy, irand,QMusuh,round);
// 	CommandPanel(gameState, enemy, info);
// 	CommandInputShow(gameState, enemy, QPlayer);wprintf(L"\n");
// }

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