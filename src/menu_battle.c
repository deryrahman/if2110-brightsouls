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
int HP=20;
int STR=5;
int DEF=3;
int Round=1;
int EHP=50;
int ESTR=10;
int EDEF=8;
int i,j,k;


Queue RandomAction();
Stack QueueToStack(Queue Q);
void CetakQ(Queue Q);
void Random2Number(int *irand);
void CommandHeader(int *irand, Queue QMusuh);
void CommandPanel(int info);
void CommandInputShow(Queue QPlayer);
void CommandInput(Queue *QPlayer, QueueInfoType *Xq);
int CommandBattle(Queue QPlayer, Queue QMusuh);
void CommandBox(Queue QMusuh, Queue QPlayer, int *irand, int info);

int main(){

	int irand[2];
	// Bikin queue pergerakan musuh
	Queue QMusuh = RandomAction();
	// Ambil 2 elemen dalam stack secara random untuk hidden tampilan aksi musuh
	Random2Number(irand);

	// Tampilan
	Queue QPlayer;
	QueueInfoType Xq;
	int curr;
	char nl,rm;
	QueueCreateEmpty(&QPlayer,4);
	int info=0;

	while(!QueueIsFull(QPlayer)){
		CommandBox(QMusuh, QPlayer, irand, info);
		CommandInput(&QPlayer,&Xq);
		
		CommandBox(QMusuh, QPlayer, irand, info);
		printf("| 'E' to remove previous command or 'C' to continue... ");
		scanf("%c",&rm);scanf("%c",&nl);
		while(rm!='E' && rm!='C'){
			printf("| WRONG INPUT! ");
			scanf("%c",&rm);scanf("%c",&nl);
		}
		if(rm=='E'){
			QueueDel(&QPlayer,&Xq);
		} else if (rm=='C'){
			curr=QueueNBElmt(QPlayer)-1;

			// eksekusi hasil
			info=CommandBattle(QPlayer,QMusuh);

			//jika irand sama dengan NbElmt SPlayer, maka ubah nilainya
			irand[0]=(curr==irand[0])?4:irand[0];
			irand[1]=(curr==irand[1])?4:irand[1];
		}
	}
		CommandBox(QMusuh, QPlayer, irand, info);
	return 0;
}

Queue RandomAction(){
	Queue Q;
	QueueInfoType Xq;
	QueueCreateEmpty(&Q,4);
	while(!QueueIsFull(Q)){
		int irand = (rand() % 4)-1;
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

void CommandHeader(int *irand, Queue QMusuh){
	printf("|====================================================================================================\n");
	printf("| PLAYER : %s | LVL : %d | HP : %d | STR : %d | DEF : %d | Round : %d |\n", Name, LVL, HP, STR, DEF, Round);
	printf("|====================================================================================================\n");
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
	printf("|====================================================================================================|\n");
}
void CommandPanel(int info){
	printf("|\n| ");
	switch (info) {
		case 1 : printf("DRAW\n|"); break;
		case 2 : printf("PLAYER Attack! But it's blocked.\n| HP ENEMY : +%d", EDEF/2); break;
		case 3 : printf("PLAYER Attack! It's very effective.\n| HP ENEMY : -%d",STR); break;
		case 4 : printf("ENEMY Attack! But it's blocked.\n| HP PLAYER : +%d", DEF/2); break;
		case 5 : printf("ENEMY Flank! Bad decision dude.\n| HP PLAYER : -%d",ESTR*2); break;
		case 6 : printf("ENEMY Attack! Bad decision dude.\n| HP PLAYER : -%d",ESTR); break;
		case 7 : printf("USER Flank! It's very effective.\n| HP ENEMY : -%d",STR*2); break;
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
void CommandBox(Queue QMusuh, Queue QPlayer, int *irand, int info){
	system("clear");
	CommandHeader(irand,QMusuh);
	CommandPanel(info);
	CommandInputShow(QPlayer);printf("\n");
}