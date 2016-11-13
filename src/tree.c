/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 07/11/2016
File	: tree.c
*/

#include <stdio.h>
#include "../include/tree.h" // masih dijalankan terpisah dari main utama

Tree TreeCreate(){
	return TreeAlloc(SkillCreate(0,0));
}
TreeAddress TreeAlloc(Skill X){
	TreeAddress P=(TreeAddress) malloc(sizeof(Node));
	if(P!=Nil){
		TreeRoot(P)=X;
		TreeLeft(P)=Nil;
		TreeRight(P)=Nil;
	}
	return P;
}
void TreeDealloc(TreeAddress P){
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
void TreeAddLeft(Tree P, Skill X, TreeAddress *Pl){
	TreeAddress PLeft=TreeAlloc(X);
	TreeLeft(P)=PLeft;
	*Pl=PLeft;
}
void TreeAddRight(Tree P, Skill X, TreeAddress *Pr){
	TreeAddress PRight=TreeAlloc(X);
	TreeRight(P)=PRight;
	*Pr=PRight;
}
void TreePrint(Tree P){
	// if (TreeLeft(P)==Nil && TreeRight(P)==Nil){
	// 	printf("[%d]",TreeRoot(P));
	// } else {
	// 	printf("%d->",TreeRoot(P));
	// 	TreePrint(TreeLeft(P));
	// 	TreePrint(TreeRight(P));
	// }
}
void TreePrintActivated(Tree P, int curr){
	if (P == Nil)
		return;
	if (TreeStatus(P)==true){
		if ((TreeLeft(P) == Nil || !TreeStatus(TreeLeft(P))) && (TreeRight(P) == Nil || !TreeStatus(TreeRight(P)))) {
		//if (TreeStatus(TreeLeft(P))==false && TreeStatus(TreeRight(P))==false){
			for(int i=0;i<curr;i++){
				printf("|   ");
			}
			printf("|-Attack : %u | Deffense : %u\n",TreeRoot(P).attack,TreeRoot(P).deffense);
		} else {
			for(int i=0;i<curr;i++){
				printf("|   ");
			}
			printf("|-Attack : %u | Deffense : %u\n",TreeRoot(P).attack,TreeRoot(P).deffense);
			TreePrintActivated(TreeLeft(P),curr+1);
			TreePrintActivated(TreeRight(P),curr+1);
		}
	}
}
