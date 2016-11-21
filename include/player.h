#ifndef _H_PLAYER
#define _H_PLAYER

#include <stdio.h>
#include "xstring.h"

typedef struct {
  String name;
  int HP;
  int EXP;
  int MAXHP;
  int STRSKILL;
  int DEFSKILL;
  int STR;
  int DEF;
  int LVL;
  int SP;
} Player;

typedef Player Enemy;

//void loadNama(FILE *FStats,String *Nama, int *Pos);
/*Merubah teks nama menjadi variable nama di program*/

int loadHP(FILE *FStats,int *PosOut);
/*Merubah teks HP dari file playerstats.txt menjadi internal variable
  I.S. = Internal variable kosong
  F.S. = Internal variable terisi oleh HP dari eksternal file, berupa integer*/

int loadSTR(FILE *FStats,int PosIn,int *PosOut);
/*Merubah teks STR dari file playerstats.txt menjadi internal variable
  I.S. = Internal variable kosong
  F.S. = Internal variable terisi oleh STR dari eksternal file, berupa integer*/

int loadLVL(FILE *FStats,int PosIn,int *PosOut);
/*Merubah teks LVL dari file playerstats.txt menjadi internal variable
  I.S. = Internal variable kosong.
  F.S. = Internal variable terisi oleh LVL dari eksternal file, berupa integer*/

int loadDEF(FILE *FStats,int PosIn,int *PosOut);
/*Merubah teks DEF dari file playerstats.txt menjadi internal variable
  I.S. = Internal variable kosong.
  F.S. = Internal variable terisi oleh DEF dari eksternal file, berupa integer*/

int loadSP(FILE *FStats,int PosIn);
/*Merubah teks SP(Skill Point) dari file playerstats.txt menjadi internal variable
  I.S. = Internal variable kosong.
  F.S. = Internal variable terisi oleh SP dari eksternal file, berupa integer*/

int CharToInt(char cc);
/*Mengkonversi char menjadi int
  I.S. = Char 0,1,2,..,9.
  F.S. = Integer 0,1,..,9.*/

void TulisStats(int HP, int STR, int DEF, int LVL, int SP);
/*Menuliskan stats ke file eksternal, seperti save, tapi buat statesnya
  I.S. = Stats yang lama
  F.S. = Stats yang baru, ditulis dengan mode write*/

void NewGame();
/*Menuliskan stats ke file eksternal untuk memulai game baru
  I.S. = File sembarang
  F.S. = File berisikan stats baru: Nama dan semua stats jadi 0*/

void LevelUp(int HP, int STR, int DEF, int *LVL, int *SP);
/*Menuliskan stats ke file eksternal saat naik level
  I.S. = File sembarang
  F.S. = File berisikan stats baru: Level naik 1, Stats naik  , SP naik*/


#endif
