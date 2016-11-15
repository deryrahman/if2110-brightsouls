/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 16/11/2016
File	: queue.h
*/
/* Model Implementasi Versi III dengan circular buffer */

#ifndef queue_H
#define queue_H

#include "boolean.h"

#define Nil 0

typedef int QueueInfoType;
typedef int QueueAddress;
typedef struct { 
	QueueInfoType * T;
	QueueAddress HEAD;
	QueueAddress TAIL;
	int MaxEl; 
} Queue;

#define QueueHead(Q) (Q).HEAD
#define QueueTail(Q) (Q).TAIL
#define QueueInfoHead(Q) (Q).T[(Q).HEAD]
#define QueueInfoTail(Q) (Q).T[(Q).TAIL]
#define QueueMaxEl(Q) (Q).MaxEl

boolean QueueIsEmpty (Queue Q);
boolean QueueIsFull (Queue Q);
int QueueNBElmt (Queue Q);
void QueueCreateEmpty (Queue * Q, int Max);
void QueueDeAlokasi(Queue * Q);
void QueueAdd (Queue * Q, QueueInfoType X);
void QueueDel (Queue * Q, QueueInfoType * X);

#endif