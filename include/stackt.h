/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 16/11/2016
File	: stackt.h
*/

#ifndef stackt_H
#define stackt_H
#include "boolean.h"

#define StackMaxEl 4

typedef char StackInfoType;
typedef int StackAddress;

typedef struct { 
	StackInfoType T[StackMaxEl+1];
	StackAddress TOP;
} Stack;

#define StackTop(S) (S).TOP
#define StackInfoTop(S) (S).T[(S).TOP]


void StackCreateEmpty (Stack *S);
boolean StackIsEmpty (Stack S);
boolean StackIsFull (Stack S);
void StackPush (Stack * S, StackInfoType X);
void StackPop (Stack * S, StackInfoType* X);
Stack StackReverse (Stack S);
int StackNbElmt(Stack S);
#endif
