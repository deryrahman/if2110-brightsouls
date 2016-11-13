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
<<<<<<< HEAD
		scanf("%u %u",&X, &Y);
		TreeAddLeft(P,SkillCreate(X,Y),&PChild);
=======
		scanf("%d",&X);
		TreeAddLeft(P,X,&PChild);
>>>>>>> 76d24d44ea92a4af69a1878d0c53912ce8de2568
		TreeStatus(PChild)=true;
		// Left Right
		scanf("%u %u",&X, &Y);
		TreeAddRight(P,SkillCreate(X,Y),&PChild);
		TreeStatus(PChild)=false;

	// Right
<<<<<<< HEAD
	scanf("%u %u",&X, &Y);
	TreeAddRight(root,SkillCreate(X,Y),&P);
		TreeStatus(P)=true;
		// Left Left
		scanf("%u %u",&X, &Y);
		TreeAddLeft(P,SkillCreate(X,Y),&PChild);
=======
	scanf("%d",&X);
	TreeAddRight(root,X,&P);
		TreeStatus(P)=true;
		// Left Left
		scanf("%d",&X);
		TreeAddLeft(P,X,&PChild);
>>>>>>> 76d24d44ea92a4af69a1878d0c53912ce8de2568
		TreeStatus(PChild)=true;
		// Left Right
		scanf("%u %u",&X, &Y);
		TreeAddRight(P,SkillCreate(X,Y),&PChild);
		TreeStatus(PChild)=true;

	TreePrint(root);printf("\n");
	TreePrintActivated(root,0);
	return 0;
}
