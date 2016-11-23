/*
 * Author
 * Nama : Jauhar Arifin
 * NIM : 13515049
 * Tanggal : Kamis, 20 Oktober 2016
 */

#include "listinteger.h"
#include "boolean.h"
#include "stdlib.h"
#include "stdio.h"

/*
 * IsEmpty
 * Mengirim true jika list kosong
 */
boolean LIIsEmpty (ListInteger L) {
	return LIFirst(L) == Nil;
}

/*
 * CreateEmpty
 * I.S. sembarang
 * F.S. Terbentuk list kosong
 */
void LICreateEmpty (ListInteger *L) {
	LIFirst(*L) = Nil;
}

/*
 * Alokasi
 * Mengirimkan address hasil alokasi sebuah elemen
 * Jika alokasi berhasil, maka address tidak nil, dan misalnya
 * menghasilkan P, maka Info(P)=X, Next(P)=Nil
 * Jika alokasi gagal, mengirimkan Nil
 */
LIaddress LIAlokasi (int X) {
	LIaddress p = (LIaddress) malloc(sizeof(int));
	if (p != Nil) {
		LIInfo(p) = X;
		LINext(p) = Nil;
	}
	return p;
}

/*
 * Dealokasi
 * I.S. P terdefinisi
 * F.S. P dikembalikan ke sistem
 * Melakukan dealokasi/pengembalian address P
 */
void LIDealokasi (LIaddress *P) {
	free(*P);
}

/*
 * Search
 * Mencari apakah ada elemen list dengan Info(P)= X
 * Jika ada, mengirimkan address elemen tersebut.
 * Jika tidak ada, mengirimkan Nil
 */
LIaddress LISearch (ListInteger L, int X) {
	LIaddress p = LIFirst(L);
	LIaddress i = Nil;
	while (i == Nil && p != Nil) {
		if (LIInfo(p) == X)
			i = p;
		p = LINext(p);
	}
	return i;
}

/*
 * FSearch
 * Mencari apakah ada elemen list yang beralamat P
 * Mengirimkan true jika ada, false jika tidak ada
 */
boolean FSearch (ListInteger L, LIaddress P) {
	LIaddress i = LIFirst(L);
	boolean found = false;
	while (!found && i != Nil) {
		if (i == P)
			found = true;
		i = LINext(i);
	}
	return found;
}

/*
 * SearchPrec
 * Mengirimkan address elemen sebelum elemen yang nilainya=X
 * Mencari apakah ada elemen list dengan Info(P)=X
 * Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X.
 * Jika tidak ada, mengirimkan Nil
 * Jika P adalah elemen pertama, maka Prec=Nil
 * Search dengan spesifikasi seperti ini menghindari
 * traversal ulang jika setelah Search akan dilakukan operasi lain
 */
LIaddress LISearchPrec (ListInteger L, int X) {
	LIaddress i = LIFirst(L);
	LIaddress bi = Nil;
	boolean found = false;
	while (!found && i != Nil)
		if (LIInfo(i) == X)
			found = true;
		else {
			bi = i;
			i = LINext(i);
		}
	return found ? bi : Nil;
}

/*
 * InsVFirst
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen pertama dengan nilai X jika alokasi berhasil
 */
void LIInsVFirst (ListInteger *L, int X) {
	LIaddress p = LIAlokasi(X);
	if (p != Nil) {
		LINext(p) = LIFirst(*L);
		LIFirst(*L) = p;
	}
}

/*
 * InsVLast
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen list di akhir: elemen terakhir yang baru
 * bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S.
 */
void LIInsVLast (ListInteger *L, int X) {
	LIaddress last = Nil;
	LIaddress i = LIFirst(*L);
	while (i != Nil) {
		last = i;
		i = LINext(i);
	}

	if (last == Nil)
		LIFirst(*L) = LIAlokasi(X);
	else
		LINext(last) = LIAlokasi(X);
}

/*
 * DelVFirst
 * I.S. List L tidak kosong
 * F.S. Elemen pertama list dihapus: nilai info disimpan pada X
 *      dan alamat elemen pertama di-dealokasi
 */
void LIDelVFirst (ListInteger *L, int *X) {
	LIaddress first = LIFirst(*L);
	LIFirst(*L) = LINext(first);
	*X = LIInfo(first);
	LIDealokasi(&first);
}

/*
 * DelVLast
 * I.S. list tidak kosong
 * F.S. Elemen terakhir list dihapus: nilai info disimpan pada X
 *      dan alamat elemen terakhir di-dealokasi
 */
void LIDelVLast (ListInteger *L, int *X) {
	LIaddress last = Nil;
	LIaddress blast = Nil;
	LIaddress i = LIFirst(*L);
	while (i != Nil) {
		blast = last;
		last = i;
		i = LINext(i);
	}

	if (blast != Nil)
		LINext(blast) = Nil;
	else
		LIFirst(*L) = Nil;

	*X = LIInfo(last);
	LIDealokasi(&last);
}

int LINbElmt (ListInteger L) {
	int c = 0;
	LIaddress i = LIFirst(L);
	while (i != Nil) {
		c++;
		i = LINext(i);
	}
	return c;
}
