/*
 * Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Sabtu, 5 November 2016
 * Nama File	: player.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "xstring.h"
#include "player.h"


/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/

int CharToInt(char cc){
	if (cc=='1'){
		return 1;
	}else if (cc=='2'){
		return 2;
	}else if (cc=='3'){
		return 3;
	}else if (cc=='4'){
		return 4;
	}else if (cc=='5'){
		return 5;
	}else if (cc=='6'){
		return 6;
	}else if (cc=='7'){
		return 7;
	}else if (cc=='8'){
		return 8;
	}else if (cc=='9'){
		return 9;
	}else if (cc=='0'){
		return 0;
	} else
		return -1;

}

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/

int loadHP(FILE *FStats,int *PosOut){
	char c,HP[9];
	int i,pos=0,RealHP;
	c = fgetc(FStats);
	while (c !='|'){
		c = fgetc(FStats);
		i = CharToInt(c);
		if (i>=0 && i<=9){
			HP[pos]=c;
			HP[++pos] = 0;
		}
	}
	i = ftell(FStats);
	RealHP = atoi(HP);
	*PosOut = i;
	return RealHP;
}

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Selasa, 22 November 2016*/

int loadMaxHP(FILE *FStats,int PosIn,int *PosOut){
	char c,MHP[9],CPos;
	CPos=PosIn;
	int i,pos=0,RealMHP;
	fseek(FStats,CPos,SEEK_SET);
	c = fgetc(FStats);
	while (c !='|'){
		c = fgetc(FStats);
		i = CharToInt(c);
		if (i>=0 && i<=9){
			MHP[pos]=c;
			MHP[++pos] = 0;
		}
	}
	i = ftell(FStats);
	RealMHP = atoi(MHP);
	*PosOut = i;
	return RealMHP;
}


/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/


int loadSTR(FILE *FStats,int PosIn,int *PosOut){
	char c,STR[9],CPos;
	CPos=PosIn;
	int i,pos=0,RealSTR;
	fseek(FStats,CPos,SEEK_SET);
	c = fgetc(FStats);
	while (c !='|'){
		c = fgetc(FStats);
		i = CharToInt(c);
		if (i>=0 && i<=9){
			STR[pos]=c;
			STR[++pos] = 0;
		}
	}
	i = ftell(FStats);
	RealSTR = atoi(STR);
	*PosOut = i;
	return RealSTR;
}


/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/


int loadLVL(FILE *FStats,int PosIn,int *PosOut){
	char c,LVL[9],CPos;
	CPos=PosIn;
	int i,pos=0,RealLVL;
	fseek(FStats,CPos,SEEK_SET);
	c = fgetc(FStats);
	while (c !='|'){
		c = fgetc(FStats);
		i = CharToInt(c);
		if (i>=0 && i<=9){
			LVL[pos]=c;
			LVL[++pos] = 0;
		}
	}
	i = ftell(FStats);
	RealLVL = atoi(LVL);
	*PosOut = i;
	return RealLVL;
}

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/


int loadDEF(FILE *FStats,int PosIn,int *PosOut){
	char c,DEF[9],CPos;
	CPos=PosIn;
	int i,pos=0,RealDEF;
	fseek(FStats,CPos,SEEK_SET);
	c = fgetc(FStats);
	while (c !='|'){
		c = fgetc(FStats);
		i = CharToInt(c);
		if (i>=0 && i<=9){
			DEF[pos]=c;
			DEF[++pos] = 0;
		}
	}
	i = ftell(FStats);
	RealDEF = atoi(DEF);
	*PosOut = i;
	return RealDEF;
}

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/


int loadSP(FILE *FStats,int PosIn,int *PosOut){
	char c,SP[9],CPos;
	CPos=PosIn;
	int i,pos=0,RealSP;
	fseek(FStats,CPos,SEEK_SET);
	c = fgetc(FStats);
	while (c !='|'){
		c = fgetc(FStats);
		i = CharToInt(c);
		if (i>=0 && i<=9){
			SP[pos]=c;
			SP[++pos] = 0;
		}
	}
	i = ftell(FStats);
	RealSP = atoi(SP);
	*PosOut = i;
	return RealSP;
}

int loadEXP(FILE *FStats,int PosIn,int *PosOut){
	char c,EXP[9],CPos;
	CPos=PosIn;
	int i,pos=0,RealEXP;
	fseek(FStats,CPos,SEEK_SET);
	c = fgetc(FStats);
	while (c !='|' && c != '\n' && c != '\r' && c != 0 && c != EOF){
		c = fgetc(FStats);
		i = CharToInt(c);
		if (i>=0 && i<=9){
			EXP[pos]=c;
			EXP[++pos] = 0;
		}
	}
	i = ftell(FStats);
	RealEXP = atoi(EXP);
	*PosOut = i;
	return RealEXP;
}

/*String loadName(FILE *FStats,int PosIn,int *PosOut){
	char c,CPos;
	String Name;
	StringCreate(Name)
	CPos=PosIn;
	int i,pos=0,RealEXP;
	fseek(FStats,CPos,SEEK_SET);
	c = fgetc(FStats);
	while (c !='|'){
		c = fgetc(FStats);
		i = CharToInt(c);
		if ((!(i>=0 && i<=9)) && c!=' '){
			Name[pos]=c;
			Name[++pos] = 0;
		}
	}
	i = ftell(FStats);
	*PosOut = i;
	return Name;
}*/

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/


void TulisStats(String filename, String name, int HP,int MaxHP, int STR, int DEF, int LVL, int SP, int EXP){
	FILE *FStats2 = fopen(filename,"w");
	fprintf(FStats2,"%s\nHP: %d | MAXHP: %d | STR: %d | DEF: %d | LVL: %d | SP: %d | EXP: %d",name, HP, MaxHP,STR,DEF,LVL,SP,EXP);
	fclose(FStats2);
}

Player* LoadPlayerFromFile(String path) {
	FILE *file = fopen(path, "r");
	if (file) {
		Player* player = (Player*) malloc(sizeof(Player));
		player->name = StringCreate("");
		StringFreadln(&player->name, file);

		int pos = 0;
		player->HP = loadHP(file, &pos);
		player->MAXHP = loadMaxHP(file, pos, &pos);
		player->STR = loadSTR(file, pos, &pos);
		player->DEF = loadDEF(file, pos, &pos);
		player->LVL = loadLVL(file, pos, &pos);
		player->SP = loadSP(file, pos, &pos);
		player->EXP = loadEXP(file, pos, &pos);
		player->STRSKILL = 0;
		player->DEFSKILL = 0;
		return player;
	} else
		return NULL;
}

Player* PlayerNew(String name) {
	Player* player = (Player*) malloc(sizeof(Player));
	player->name = name;
	player->HP = 20;
	player->MAXHP = 20;
	player->STR = 1;
	player->DEF = 1;
	player->LVL = 1;
	player->SP = 0;
	player->EXP = 0;
	player->STRSKILL = 0;
	player->DEFSKILL = 0;

	return player;
}

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/

void NewGame(String name, String filename){
	TulisStats(filename,name,20,20,1,1,1,0,0);
}

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/

/*void loadNama(FILE *FStats,String *Nama, int *Pos){
	char c[20],cc;
	int i=0,len;

}*/

/* Author
 * Nama			: Aulia Ichsan RIfkyano
 * Hari/Tanggal : Minggu, 6 November 2016*/

void LevelUp(int HP,int MaxHP, int STR, int DEF, int *LVL, int *SP,int EXP){
	int Level = (*LVL)+1;
	int SPU	  = (*SP)+5;
	MaxHP 	  = Level*20;
	//TulisStats(HP,MaxHP,STR,DEF,Level,SPU,EXP);
	*LVL 	=Level;
	*SP		=SPU;
}
