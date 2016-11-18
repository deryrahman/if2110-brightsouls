/* Driver */

#include <stdio.h>
#include "../include/tree.h" // masih dijalankan terpisah dari main utama

int main(){
	uint X,Y;

	TreeAddress P,PChild;
	Tree root=TreeAlloc(SkillCreate(10,5,10));
	// Left 
	TreeAddLeft(root,SkillCreate(10,5,20),&P);
		// Left Left
		TreeAddLeft(P,SkillCreate(20,5,40),&PChild);
		// Left Right
		TreeAddRight(P,SkillCreate(5,20,50),&PChild);

	// Right
	TreeAddRight(root,SkillCreate(5,10,30),&P);
		// Left Left
		TreeAddLeft(P,SkillCreate(15,10,60),&PChild);
		// Left Right
		TreeAddRight(P,SkillCreate(10,15,70),&PChild);

	printf("\n");
	printf("SKILL :\n");
	TreePrint(root,0);printf("\n\n");
	printf("ACTIVATED SKILL :\n");
	TreePrintActivated(root,0);printf("\n");
	printf("TOTAL SKILL :\n");
	printf("++%u\n++%u\n", SkillTotalAttack(root), SkillTotalDeffense(root));
	return 0;
}