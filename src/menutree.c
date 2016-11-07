#include <stdio.h>
#include "../include/tree.h" // masih dijalankan terpisah dari main utama

int main(){
	int X;
	address P,PChild;
	scanf("%d",&X);
	Tree root=TreeAlloc(X);
	// Left 
	scanf("%d",&X);
	TreeAddLeft(root,X,&P);
		// Left Left
		scanf("%d",&X);
		TreeAddLeft(P,X,&PChild);
		// Left Right
		scanf("%d",&X);
		TreeAddRight(P,X,&PChild);

	// Right
	scanf("%d",&X);
	TreeAddRight(root,X,&P);
		// Left Left
		scanf("%d",&X);
		TreeAddLeft(P,X,&PChild);
		// Left Right
		scanf("%d",&X);
		TreeAddRight(P,X,&PChild);

	TreePrint(root);
	return 0;
}