/*
 * Author
 * Nama : Jauhar Arifin
 * NIM : 13515049
 * Tanggal : Kamis, 20 Oktober 2016
 */

#include "liststring.h"
#include "xstring.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * LSIsEmpty
 * Mengirim true jika list kosong
 */
boolean LSIsEmpty (StringList L) {
	return First(L) == Nil;
}

/*
 * CreateEmpty
 * I.S. sembarang
 * F.S. Terbentuk list kosong
 */
void LSCreateEmpty (StringList *L) {
	First(*L) = Nil;
}

/*
 * Alokasi
 * Mengirimkan address hasil alokasi sebuah elemen
 * Jika alokasi berhasil, maka address tidak nil, dan misalnya
 * menghasilkan P, maka Info(P)=X, Next(P)=Nil
 * Jika alokasi gagal, mengirimkan Nil
 */
Stringaddress LSAlokasi (String X) {
	Stringaddress p = (Stringaddress) malloc(sizeof(StringElmtList));
	if (p != Nil) {
		Info(p) = X;
		Next(p) = Nil;
	}
	return p;
}

/*
 * Dealokasi
 * I.S. P terdefinisi
 * F.S. P dikembalikan ke sistem
 * Melakukan dealokasi/pengembalian address P
 */
void LSDealokasi (Stringaddress *P) {
	free(*P);
}

/*
 * Search
 * Mencari apakah ada elemen list dengan Info(P)= X
 * Jika ada, mengirimkan address elemen tersebut.
 * Jika tidak ada, mengirimkan Nil
 */
Stringaddress LSSearch (StringList L, String X) {
	Stringaddress p = First(L);
	Stringaddress i = Nil;
	while (i == Nil && p != Nil) {
		if (Info(p) == X)
			i = p;
		p = Next(p);
	}
	return i;
}

/*
 * FSearch
 * Mencari apakah ada elemen list yang beralamat P
 * Mengirimkan true jika ada, false jika tidak ada
 */
boolean LSFSearch (StringList L, Stringaddress P) {
	Stringaddress i = First(L);
	boolean found = false;
	while (!found && i != Nil) {
		if (i == P)
			found = true;
		i = Next(i);
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
Stringaddress LSSearchPrec (StringList L, String X) {
	Stringaddress i = First(L);
	Stringaddress bi = Nil;
	boolean found = false;
	while (!found && i != Nil)
		if (Info(i) == X)
			found = true;
		else {
			bi = i;
			i = Next(i);
		}
	return found ? bi : Nil;
}

/*
 * InsVFirst
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen pertama dengan nilai X jika alokasi berhasil
 */
void LSInsVFirst (StringList *L, String X) {
	Stringaddress p = LSAlokasi(X);
	if (p != Nil) {
		Next(p) = First(*L);
		First(*L) = p;
	}
}

/*
 * InsVLast
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen list di akhir: elemen terakhir yang baru
 * bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S.
 */
void LSInsVLast (StringList *L, String X) {
	Stringaddress last = Nil;
	Stringaddress i = First(*L);
	while (i != Nil) {
		last = i;
		i = Next(i);
	}

	if (last == Nil)
		First(*L) = LSAlokasi(X);
	else
		Next(last) = LSAlokasi(X);
}

/*
 * DelVFirst
 * I.S. List L tidak kosong
 * F.S. Elemen pertama list dihapus: nilai info disimpan pada X
 *      dan alamat elemen pertama di-dealokasi
 */
void LSDelVFirst (StringList *L, String *X) {
	Stringaddress first = First(*L);
	First(*L) = Next(first);
	*X = Info(first);
	LSDealokasi(&first);
}

/*
 * DelVLast
 * I.S. list tidak kosong
 * F.S. Elemen terakhir list dihapus: nilai info disimpan pada X
 *      dan alamat elemen terakhir di-dealokasi
 */
void LSDelVLast (StringList *L, String *X) {
	Stringaddress last = Nil;
	Stringaddress blast = Nil;
	Stringaddress i = First(*L);
	while (i != Nil) {
		blast = last;
		last = i;
		i = Next(i);
	}

	if (blast != Nil)
		Next(blast) = Nil;
	else
		First(*L) = Nil;

	*X = Info(last);
	LSDealokasi(&last);
}

/*
 * InsertFirst
 * I.S. Sembarang, P sudah dialokasi
 * F.S. Menambahkan elemen ber-Stringaddress P sebagai elemen pertama
 */
void LSInsertFirst (StringList *L, Stringaddress P) {
	Next(P) = First(*L);
	First(*L) = P;
}

/*
 * InsertAfter
 * I.S. Prec pastilah elemen list dan bukan elemen terakhir,
 *      P sudah dialokasi
 * F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
 */
void LSInsertAfter (StringList *L, Stringaddress P, Stringaddress Prec) {
	Next(P) = Next(Prec);
	Next(Prec) = P;
}

/*
 * InsertLast
 * I.S. Sembarang, P sudah dialokasi
 * F.S. P ditambahkan sebagai elemen terakhir yang baru
 */
void LSInsertLast (StringList *L, Stringaddress P) {
	Stringaddress last = Nil;
	Stringaddress i = First(*L);
	while (i != Nil) {
		last = i;
		i = Next(i);
	}

	Next(P) = Nil;
	if (last == Nil)
		First(*L) = P;
	else
		Next(last) = P;
}

/*
 * DelFirst
 * I.S. List tidak kosong
 * F.S. P adalah alamat elemen pertama list sebelum penghapusan
 *      Elemen list berkurang satu (mungkin menjadi kosong)
 * First element yg baru adalah suksesor elemen pertama yang lama
 */
void LSDelFirst (StringList *L, Stringaddress *P) {
	Stringaddress first = First(*L);
	First(*L) = Next(first);
	*P = first;
}

/*
 * DelP
 * I.S. Sembarang
 * F.S. Jika ada elemen list beraddress P, dengan Info(P)=X
 * 		Maka P dihapus dari list dan di-dealokasi
 * 		Jika tidak ada elemen list dengan Info(P)=X, maka list tetap
 * 		List mungkin menjadi kosong karena penghapusan
 */
void LSDelP (StringList *L, String X) {
	Stringaddress bi = Nil;
	Stringaddress i = First(*L);
	while (i != Nil)
		if (Info(i) == X) {
			if (bi != Nil)
				Next(bi) = Next(i);
			else
				First(*L) = Next(i);
			Stringaddress tmp = Next(i);
			LSDealokasi(&i);
			i = tmp;
		} else {
			bi = i;
			i = Next(i);
		}
}

/*
 * DelLast
 * I.S. List tidak kosong
 * F.S. P adalah alamat elemen terakhir list sebelum penghapusan
 *      Elemen list berkurang satu (mungkin menjadi kosong)
 * Last element baru adalah predesesor elemen pertama yg lama,
 * jika ada
 */
void LSDelLast (StringList *L, Stringaddress *P) {
	Stringaddress blast = Nil;
	Stringaddress last = Nil;
	Stringaddress i = First(*L);
	while (i != Nil) {
		blast = last;
		last = i;
		i = Next(i);
	}

	*P = last;
	if (blast != Nil)
		Next(blast) = Nil;
	else
		First(*L) = Nil;
}

/*
 * DelAfter
 * I.S. List tidak kosong. Prec adalah anggota list
 * F.S. Menghapus Next(Prec):
 *      Pdel adalah alamat elemen list yang dihapus
 */
void LSDelAfter (StringList *L, Stringaddress *Pdel, Stringaddress Prec) {
	*Pdel = Next(Prec);
	if (*Pdel != Nil)
		Next(Prec) = Next(*Pdel);
}

/*
 * NbElmt
 * Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong
 */
int LSNbElmt (StringList L) {
	int c = 0;
	Stringaddress i = First(L);
	while (i != Nil) {
		c++;
		i = Next(i);
	}
	return c;
}

/*
 * DelAll
 * Delete semua elemen list dan alamat elemen di-dealokasi
 */
void LSDelAll (StringList *L) {
	Stringaddress i = First(*L);
	while (i != Nil) {
		Stringaddress tmp = Next(i);
		LSDealokasi(&i);
		i = tmp;
	}
	First(*L) = Nil;
}

/*
 * InverseList
 * I.S. sembarang.
 * F.S. elemen list dibalik :
 * Elemen terakhir menjadi elemen pertama, dan seterusnya.
 * Membalik elemen list, tanpa melakukan alokasi/dealokasi.
 */
void LSInversList (StringList *L) {
	Stringaddress i = First(*L);
	Stringaddress j = Nil;
	Stringaddress k = Nil;
	while (i != Nil) {
		if (j != Nil)
			Next(j) = k;
		k = j;
		j = i;
		i = Next(i);
	}
	if (j != Nil)
		Next(j) = k;
	First(*L) = j;
}

/*
 * FInversList
 * Mengirimkan list baru, hasil invers dari L
 * dengan menyalin semua elemn list. Alokasi mungkin gagal.
 * Jika alokasi gagal, hasilnya list kosong
 * dan semua elemen yang terlanjur di-alokasi, harus didealokasi
 */
StringList LSFInversList (StringList L) {
	boolean gagal = false;
	StringList baru;
	LSCreateEmpty(&baru);

	Stringaddress i = First(L);
	while (!gagal && i != Nil) {
		Stringaddress aloc = LSAlokasi(Info(i));
		if (aloc == Nil)
			gagal = true;

		if (!gagal) {
			Next(aloc) = First(baru);
			First(baru) = aloc;
			i = Next(i);
		}
	}

	if (gagal)
		LSDelAll(&baru);

	return baru;
}

/*
 * CopyList
 * I.S. L1 sembarang. F.S. L2=L1
 * L1 dan L2 "menunjuk" kepada list yang sama.
 * Tidak ada alokasi/dealokasi elemen
 */
void LSCopyList (StringList *L1, StringList *L2) {
	First(*L2) = First(*L1);
}

/*
 * FCopyList
 * Mengirimkan list yang merupakan salinan L
 * dengan melakukan alokasi.
 * Jika ada alokasi gagal, hasilnya list kosong dan
 * semua elemen yang terlanjur di-alokasi, harus didealokasi
 */
StringList LSFCopyList (StringList L) {
	boolean gagal = false;
	StringList baru;
	LSCreateEmpty(&baru);
	Stringaddress last = First(baru);

	Stringaddress i = First(L);
	while (!gagal && i != Nil) {
		Stringaddress aloc = LSAlokasi(Info(i));
		if (aloc == Nil)
			gagal = true;

		if (!gagal) {
			if (last == Nil)
				last = First(baru) = aloc;
			else {
				Next(last) = aloc;
				last = Next(last);
			}
			Next(last) = Nil;
		}

		i = Next(i);
	}

	if (gagal)
		LSDelAll(&baru);

	return baru;
}

/*
 * CpAlokList
 * I.S. Lin sembarang.
 * F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin
 * Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi
 * dengan melakukan alokasi elemen.
 * Lout adalah list kosong jika ada alokasi elemen yang gagal
 */
void LSCpAlokList (StringList Lin, StringList *Lout) {
	*Lout = LSFCopyList(Lin);
}

/*
 * Konkat
 * I.S. L1 dan L2 sembarang
 * F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2
 * Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi
 * Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi
 * harus di-dealokasi dan L3=Nil
 * Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru"
 * Elemen L3 adalah hasil alokasi elemen yang "baru".
 * Jika ada alokasi yang gagal, maka L3 harus bernilai Nil
 * dan semua elemen yang pernah dialokasi didealokasi
 */
void LSKonkat (StringList L1, StringList L2, StringList * L3) {
	boolean gagal = false;
	LSCreateEmpty(L3);
	Stringaddress last = First(*L3);

	Stringaddress i = First(L1);
	boolean still_l1 = true;
	if (i == Nil) {
		i = First(L2);
		still_l1 = false;
	}
	while (!gagal && i != Nil) {
		Stringaddress aloc = LSAlokasi(Info(i));
		if (aloc == Nil)
			gagal = true;

		if (!gagal) {
			if (last == Nil)
				last = First(*L3) = aloc;
			else {
				Next(last) = aloc;
				last = Next(last);
			}
			Next(last) = Nil;
		}

		i = Next(i);
		if (i == Nil && still_l1) {
			still_l1 = false;
			i = First(L2);
		}
	}

	if (gagal)
		LSDelAll(L3);
}

/*
 * Konkat1
 * I.S. L1 dan L2 sembarang
 * F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2
 * Konkatenasi dua buah list : L1 dan L2
 * menghasilkan L3 yang baru (dengan elemen list L1 dan L2)
 * dan L1 serta L2 menjadi list kosong.
 * Tidak ada alokasi/dealokasi pada prosedur ini
 */
void LSKonkat1 (StringList *L1, StringList *L2, StringList *L3) {
	if (LSIsEmpty(*L1))
		First(*L3) = First(*L2);
	else {
		First(*L3) = First(*L1);
		Stringaddress last = Nil;
		Stringaddress i = First(*L1);
		while (i != Nil) {
			last = i;
			i = Next(i);
		}
		Next(last) = First(*L2);
	}

	First(*L1) = First(*L2) = Nil;
}

/*
 * PecahList
 * I.S. L mungkin kosong
 * F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2
 * L tidak berubah: untuk membentuk L1 dan L2 harus alokasi
 * L1 berisi separuh elemen L dan L2 berisi sisa elemen L
 * Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2
 */
void LSPecahList (StringList *L1, StringList *L2, StringList L) {
	int separuh = LSNbElmt(L) / 2;
	int counter = 0;

	LSCreateEmpty(L1);
	LSCreateEmpty(L2);
	Stringaddress last = First(*L1);

	Stringaddress i = First(L);
	while (i != Nil) {
		counter++;

		Stringaddress aloc = LSAlokasi(Info(i));

		if (last == Nil) {
			last = counter > separuh ? (First(*L2) = aloc) : (First(*L1) = aloc);
		} else {
			Next(last) = aloc;
			last = Next(last);
		}

		if (counter == separuh) {
			Next(last) = Nil;
			last = Nil;
		}

		i = Next(i);
	}
}
