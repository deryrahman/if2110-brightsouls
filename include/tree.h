/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 07/11/2016
File	: tree.h
*/

#ifndef _TREE_H
#define _TREE_H
#include "boolean.h"
#include "integer.h"
#include "skill.h"
#include <stdlib.h>

#define Nil NULL

typedef struct tNode *TreeAddress;
typedef struct tNode {
	boolean status;
	Skill info;
	TreeAddress left;
	TreeAddress right;
} Node;
typedef TreeAddress Tree;

/* Selektor */
#define TreeStatus(P) (P)->status
#define TreeRoot(P) (P)->info
#define TreeLeft(P) (P)->left
#define TreeRight(P) (P)->right

Tree TreeCreate();
TreeAddress TreeAlloc(Skill X);
void TreeDealloc(TreeAddress P);
boolean TreeIsEmpty(Tree P);
boolean TreeIsOneElmt(Tree P);
void TreeAddLeft(Tree P, Skill X, TreeAddress *Pl);
void TreeAddRight(Tree P, Skill X, TreeAddress *Pr);
void TreePrint(Tree P, int curr);
void TreePrintActivated(Tree P, int curr);
uint SkillTotalAttack(Tree P);
uint SkillTotalDeffense(Tree P);

#endif