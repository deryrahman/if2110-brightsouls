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
	return QueueHead(Q)==0 && QueueTail(Q)==0;
}
boolean QueueIsFull (Queue Q){
	return ((QueueHead(Q)==1) && (QueueTail(Q)==QueueMaxEl(Q)));
}
int QueueNBElmt (Queue Q){
	return (QueueTail(Q)-QueueHead(Q)+1);
}

void QueueCreateEmpty (Queue * Q, int Max){
	(*Q).T = (QueueInfoType *) malloc ((Max+1) * sizeof(QueueInfoType));
	if ((*Q).T != NULL) {
		QueueMaxEl(*Q) = Max;
		QueueHead(*Q) = 0;
		QueueTail(*Q) = 0;
	} else /* alokasi gagal */ {
		QueueMaxEl(*Q) = 0;
	}
}
void DeAlokasi(Queue * Q){
	QueueMaxEl(*Q)=0;
	free((*Q).T);
}

void QueueAdd (Queue * Q, QueueInfoType X){
	QueueAddress i,j;

	if (QueueIsEmpty(*Q)) {
		QueueHead(*Q)=1;
	} else /* Q tidak kosong */ {
		if (QueueTail(*Q)==QueueMaxEl(*Q)) { /* Geser elemen smp Head(Q)=1 */
			i = QueueHead(*Q);
			j = 1;
			do { 
				*((*Q).T+j) = *((*Q).T+i);
				i++; j++;
			} while (i<=QueueTail(*Q));
		}
		QueueTail(*Q) = QueueNBElmt(*Q);
		QueueHead(*Q) = 1;
	}
	QueueTail(*Q)++;
	QueueInfoTail(*Q)=X;
}
void QueueDel(Queue * Q, QueueInfoType * X){
	*X = QueueInfoHead(*Q);
	if (QueueHead(*Q)==QueueTail(*Q)) {
		QueueHead(*Q)=0;
		QueueTail(*Q)=0;
	}
	else {
		QueueHead(*Q)++;
	}
}
void QueueDelLast(Queue * Q, QueueInfoType * X){
	*X = QueueInfoTail(*Q);
	if (QueueHead(*Q)==QueueTail(*Q)) {
		QueueHead(*Q)=0;
		QueueTail(*Q)=0;
	}
	else {
		QueueTail(*Q)--;
	}
}
void QueueCopy (Queue Q, Queue *Qout){
	QueueInfoType Xq;
	while(!QueueIsEmpty(Q)){
		QueueDel(&Q,&Xq);
		QueueAdd(Qout,Xq);
	}
}