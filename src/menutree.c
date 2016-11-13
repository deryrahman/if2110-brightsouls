#include <stdio.h>
#include "../include/tree.h" // masih dijalankan terpisah dari main utama

int main(){
	uint X,Y;

	TreeAddress P,PChild;
	scanf("%u %u",&X, &Y);
	Tree root=TreeAlloc(SkillCreate(X,Y));
	TreeStatus(root)=true;
	// Left 
	scanf("%u %u",&X, &Y);
	TreeAddLeft(root,SkillCreate(X,Y),&P);
		TreeStatus(P)=true;
		// Left Left
		scanf("%u %u",&X, &Y);
		TreeAddLeft(P,SkillCreate(X,Y),&PChild);
		TreeStatus(PChild)=true;
		// Left Right
		scanf("%u %u",&X, &Y);
		TreeAddRight(P,SkillCreate(X,Y),&PChild);
		TreeStatus(PChild)=false;

	// Right
	scanf("%u %u",&X, &Y);
	TreeAddRight(root,SkillCreate(X,Y),&P);
		TreeStatus(P)=true;
		// Left Left
		scanf("%u %u",&X, &Y);
		TreeAddLeft(P,SkillCreate(X,Y),&PChild);
		TreeStatus(PChild)=true;
		// Left Right
		scanf("%u %u",&X, &Y);
		TreeAddRight(P,SkillCreate(X,Y),&PChild);
		TreeStatus(PChild)=true;

	TreePrint(root,0);printf("\n");
	TreePrintActivated(root,0);
	printf("%u\n%u\n", SkillTotalAttack(root), SkillTotalDeffense(root));
	return 0;
}
