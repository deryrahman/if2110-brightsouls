/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 16/11/2016
File	: stackt.c
*/

#include <stdio.h>
#include "../include/stackt.h" // masih dijalankan terpisah dari main utama

void StackCreateEmpty (Stack *S){
	StackTop(*S)=0;
}

boolean StackIsEmpty (Stack S){
	return StackTop(S)==0;
}
boolean StackIsFull (Stack S){
	return StackTop(S)==StackMaxEl;
}

void StackPush (Stack * S, StackInfoType X){
	StackTop(*S)++;
	StackInfoTop(*S)=X;
}

void StackPop (Stack * S, StackInfoType* X){
	*X=StackInfoTop(*S);
	StackTop(*S)--;
}