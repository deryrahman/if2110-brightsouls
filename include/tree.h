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
#include <stdlib.h>

#define Nil NULL

typedef int infotype;
typedef struct tNode *address;
typedef struct tNode {
	infotype info;
	address left;
	address right;
} Node;
typedef address Tree;

/* Selektor */
#define TreeRoot(P) (P)->info
#define TreeLeft(P) (P)->left
#define TreeRight(P) (P)->right

address TreeAlloc(infotype X);
void TreeDealloc(address P);
boolean TreeIsEmpty(Tree P);
boolean TreeIsOneElmt(Tree P);
void TreeAddLeft(Tree P, infotype X, address *Pl);
void TreeAddRight(Tree P, infotype X, address *Pr);
void TreePrint(Tree P);

#endif