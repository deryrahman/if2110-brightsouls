/* Driver */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../include/tree.h" // masih dijalankan terpisah dari main utama
#include "../include/stackt.h" // masih dijalankan terpisah dari main utama
#include "../include/queue.h" // masih dijalankan terpisah dari main utama
#include "../include/xstring.h" // masih dijalankan terpisah dari main utama

// GLOBAL VARIABLE

String Name="Dery";
String EName="Lucifer";
int LVL=1;
int HPMAX=20;
int STR=5;
int DEF=3;
int Round=1;
int EHPMAX=50;
int ESTR=10;
int EDEF=8;
int i,j,k;
int HP=30,EHP=50;
int STRSKILL=10;
int DEFSKILL=8;

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

int main(){

	int irand[2];
	Queue QPlayer;
	QueueInfoType Xq;
	int curr;
	int info=0;
	int ronde_max=10,ronde=1;
	char nl,rm,next;
	Queue QMusuh;
	do{
		// Bikin queue pergerakan musuh
		QMusuh = RandomAction();
		// Ambil 2 elemen dalam stack secara random untuk hidden tampilan aksi musuh
		Random2Number(irand);
		// Bikin queue untuk input user
		QueueCreateEmpty(&QPlayer,4);
		info=0;
		while(!QueueIsFull(QPlayer)){
			CommandBox(QMusuh, QPlayer, irand, info, ronde);
			CommandInput(&QPlayer,&Xq);
			
			CommandBox(QMusuh, QPlayer, irand, info, ronde);
			printf("| 'E' to remove previous command or 'C' to continue... ");
			scanf("%c",&rm);scanf("%c",&nl);
			while(rm!='E' && rm!='C'){
				printf("| WRONG INPUT! ");
				scanf("%c",&rm);scanf("%c",&nl);
			}
			if(rm=='E'){
				QueueDelLast(&QPlayer,&Xq);
			} else if (rm=='C'){
				curr=QueueNBElmt(QPlayer)-1;

				// eksekusi hasil
				info=CommandBattle(QPlayer,QMusuh);

				//jika irand sama dengan NbElmt SPlayer, maka ubah nilainya
				irand[0]=(curr==irand[0])?4:irand[0];
				irand[1]=(curr==irand[1])?4:irand[1];
				CommandCalculation(STR+STRSKILL, ESTR, DEF+DEFSKILL, EDEF, &HP, &EHP, info);
			}
			if(HP<=0 || EHP<=0)
				break;
		}
		CommandBox(QMusuh, QPlayer, irand, info, ronde);
		if(HP>0 && EHP>0){
			printf("| 'C' to continue next battle... ");
			scanf("%c",&rm);scanf("%c",&nl);
			while(rm!='C'){
				printf("| WRONG INPUT! ");
				scanf("%c",&rm);scanf("%c",&nl);
			}
		}
		if(HP<=0 || EHP<=0)
				break;
		ronde++;
		QueueCreateEmpty(&QPlayer,4);
	} while (ronde<ronde_max && HP>0 && EHP>0);
	// mengembalikan QMusuh jadi empty
	if(HP<=0){
		CommandBox(QMusuh, QPlayer, irand, 9, ronde);
	} else if (EHP<=0){
		CommandBox(QMusuh, QPlayer, irand, 8, ronde);
	} else {
		CommandBox(QMusuh, QPlayer, irand, 10, ronde);
	}

	return 0;
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
		printf("%c", Xq);
	}
}

Stack QueueToStack(Queue Q){
	Stack S;
	StackInfoType Xs;
	StackCreateEmpty(&S);
	while(!StackIsFull(S)){
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

void CommandHeader(int *irand, Queue QMusuh, int round){
	printf("|====================================================================================================     SKILL : \n");
	printf("| PLAYER : %s | LVL : %d | HP : %d | STR : %d | DEF : %d | Round : %d |\n", Name, LVL, HP, STR, DEF, round);
	printf("|====================================================================================================     HP + %d | DEF + %d\n", STRSKILL, DEFSKILL);
	printf("| ENEMY : %s | HP : %d | Command : ", EName, EHP);
	
	int i=0;
	QueueInfoType Xq;
	while(i<4){
		QueueDel(&QMusuh,&Xq);
		if(irand[0]==i || irand[1]==i){
			printf("#");
		} else {
			printf("%c", Xq);
		}
		i++;
	}
	printf(" |\n");
	printf("|====================================================================================================     Press 'S' to open Skill tree\n");
}
void CommandPanel(int info){
	printf("|\n| ");
	switch (info) {
		case 1 : printf("DRAW\n|"); break;
		case 2 : printf("PLAYER Attack! But it's blocked.\n| HP ENEMY : +%d", EDEF/2); break;
		case 3 : printf("PLAYER Attack! It's very effective.\n| HP ENEMY : -%d",STR+STRSKILL); break;
		case 4 : printf("ENEMY Attack! But it's blocked.\n| HP PLAYER : +%d", (DEF+DEFSKILL)/2); break;
		case 5 : printf("ENEMY Flank! Bad decision dude.\n| HP PLAYER : -%d",ESTR*2); break;
		case 6 : printf("ENEMY Attack! Bad decision dude.\n| HP PLAYER : -%d",ESTR); break;
		case 7 : printf("USER Flank! It's very effective.\n| HP ENEMY : -%d",(STR+STRSKILL)*2); break;
		case 8 : printf("CONGRATULATION!\n| You Win!"); break;
		case 9 : printf("GAME OVER!\n| Please restart game, or load previous saved game"); break;
		case 10 : printf("DRAW!\n| Try again"); break;
		default : printf("PREPARE YOURSELF, ENEMY IS WATCHING YOU!\n| Please enter command.."); break;
	}
	printf("\n|\n|====================================================================================================\n");
}
void CommandInput(Queue *QPlayer, QueueInfoType *Xq){
	char nl;
	printf("| ");
	scanf("%c",Xq);scanf("%c",&nl);
	while (*Xq!='A' && *Xq!='B' && *Xq!='F'){
		printf("| ");
		printf("WRONG INPUT! ");
		scanf("%c",Xq);scanf("%c",&nl);
	}
		QueueAdd(QPlayer,*Xq);
}
void CommandInputShow(Queue QPlayer){
	int count=4;
	printf("| Inserted Commands : ");
	while(!QueueIsEmpty(QPlayer)){
		char Xq;
		QueueDel(&QPlayer,&Xq);
		printf("%c", Xq);
		count--;
	}
	while(count--){
		printf("_");
	}
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
}
void CommandBox(Queue QMusuh, Queue QPlayer, int *irand, int info, int round){
	system("clear");
	CommandHeader(irand,QMusuh,round);
	CommandPanel(info);
	CommandInputShow(QPlayer);printf("\n");
}

void CommandCalculation(int STR, int ESTR, int DEF, int EDEF, int *HP, int *EHP, int info){
	switch (info){
		case 2 : *EHP+=(EDEF/2); break;
		case 3 : *EHP-=(STR); break;
		case 4 : *HP+=(DEF/2); break;
		case 5 : *HP-=(ESTR*2); break;
		case 6 : *HP-=(ESTR); break;
		case 7 : *EHP-=(STR*2); break;
	}
	*EHP=(*EHP>EHPMAX)?EHPMAX:*EHP;
	*HP=(*HP>HPMAX)?HPMAX:*HP;
}