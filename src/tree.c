/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 07/11/2016
File	: tree.c
*/

#include <stdio.h>
#include "../include/tree.h"

address TreeAlloc(infotype X){
	address P=(address) malloc(sizeof(Node));
	if(P!=Nil){
		TreeRoot(P)=X;
		TreeLeft(P)=Nil;
		TreeRight(P)=Nil;
	}
	return P;
}
void TreeDealloc(address P){
	free(P);
}
boolean TreeIsEmpty(Tree P){
	return P==Nil;
}
boolean TreeIsOneElmt(Tree P){
	if (!(TreeIsEmpty(P))){
		return (TreeLeft(P)==Nil) && (TreeRight(P)==Nil);
	} else {
		return false;
	}
}
void TreeAddLeft(Tree P, infotype X, address *Pl){
	address PLeft=TreeAlloc(X);
	TreeLeft(P)=PLeft;
	*Pl=PLeft;
}
void TreeAddRight(Tree P, infotype X, address *Pr){
	address PRight=TreeAlloc(X);
	TreeRight(P)=PRight;
	*Pr=PRight;
}
void TreePrint(Tree P){
	if (TreeLeft(P)==Nil || TreeRight(P)==Nil){
		if (TreeRight(P)!=Nil){
			TreePrint(TreeRight(P));
		} else if (TreeLeft(P)!=Nil){
			TreePrint(TreeLeft(P));
		} else {
			printf("[%d]",TreeRoot(P));
		}
	} else {
		printf("%d->",TreeRoot(P));
		TreePrint(TreeLeft(P));
		TreePrint(TreeRight(P));
	}
}