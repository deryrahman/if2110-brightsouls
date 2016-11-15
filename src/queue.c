/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 16/11/2016
File	: queue.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"  // masih dijalankan terpisah dari main utama

boolean QueueIsEmpty (Queue Q){
	return QueueHead(Q)==Nil && QueueTail(Q)==Nil;
}
boolean QueueIsFull (Queue Q){
	return QueueNBElmt(Q)==QueueMaxEl(Q);
}
int QueueNBElmt (Queue Q){
	if (QueueIsEmpty(Q)){
		return 0;
	} else {
		if (QueueHead(Q)>QueueTail(Q)) {
			return (QueueMaxEl(Q)-(QueueHead(Q)-QueueTail(Q)-1));
		} else {
			return (QueueTail(Q)-QueueHead(Q)+1);
		}
	}
}

void CreateEmpty (Queue * Q, int Max){
	(*Q).T=malloc((Max+1)*sizeof(int));
	if ((*Q).T==NULL){ // Jika alokasi gagal
		QueueMaxEl(*Q)=0;
	} else {
		QueueMaxEl(*Q)=Max;
	}
	QueueHead(*Q)=0;
	QueueTail(*Q)=0;
}
void DeAlokasi(Queue * Q){
	free((*Q).T);
	QueueMaxEl(*Q)=0;
}

void QueueAdd (Queue * Q, QueueInfoType X){
	int i;

	if (QueueIsEmpty(*Q)){ // Kasus empty
		QueueHead(*Q)=1;
		QueueTail(*Q)=1;
	} else {
		if (QueueTail(*Q)==QueueMaxEl(*Q)) {
			QueueTail(*Q)=1;
		} else {
			QueueTail(*Q)++;
		}
	}
	QueueInfoTail(*Q)=X;
}
void Del(Queue * Q, QueueInfoType * X){
	*X=InfoQueueHead(*Q);
	if (QueueNBElmt(*Q)==1) { // Kasus khusus 1 elemen
		QueueHead(*Q)==Nil;
		QueueTail(*Q)==Nil;
	} else {
		if (QueueHead(*Q)==QueueMaxEl(*Q)){
			QueueHead(*Q)=1;
		} else {
			QueueHead(*Q)++;
		}
	}
}