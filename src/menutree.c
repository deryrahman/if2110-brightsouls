#include <stdio.h>
#include "../include/tree.h" // masih dijalankan terpisah dari main utama

int main(){
	int X;
	address P,PChild;
	scanf("%d",&X);
	Tree root=TreeAlloc(X);
	TreeStatus(root)=true;
	// Left 
	scanf("%d",&X);
	TreeAddLeft(root,X,&P);
		TreeStatus(P)=true;
		// Left Left
		scanf("%d",&X);
		TreeAddLeft(P,X,&PChild);
		TreeStatus(PChild)=false;
		// Left Right
		scanf("%d",&X);
		TreeAddRight(P,X,&PChild);
		TreeStatus(PChild)=false;

	// Right
	scanf("%d",&X);
	TreeAddRight(root,X,&P);
		TreeStatus(P)=false;
		// Left Left
		scanf("%d",&X);
		TreeAddLeft(P,X,&PChild);
		TreeStatus(PChild)=false;
		// Left Right
		scanf("%d",&X);
		TreeAddRight(P,X,&PChild);
		TreeStatus(PChild)=false;

	TreePrint(root);printf("\n");
	TreePrintActivated(root);
	return 0;
}