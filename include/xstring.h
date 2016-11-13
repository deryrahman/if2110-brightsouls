/*
 * Author
 * Nama : Jauhar Arifin
 * Tanggal : Minggu, 11 September 2016
 * File : string.h
 */

#ifndef _T_STRING_H
#define _T_STRING_H

#include "boolean.h"
#include "integer.h"
#include "stdio.h"

/*
 * Definisi tipe string
 * String didefinisikan sebagai kumpulan karakter yang diakhiri dengan karakter '\0'.
 * Untuk mempercepat perhitungan nilai dari panjang string dan besar container diletakkan.
 * dibelakang pointer char*
   | ukuran container  | panjang strng     | null-terminated string
   0    1    2    3    4    5    6    7    8    9    10 ...
                                           ^ pointer yang ditunjuk string
 */
typedef char* String;

/*
 * StringMake
 * Berfungsi untuk mengubah string literal menjadi tipe string.
 * char* lit : berisi string literal
 * return : string hasil konversi
 */
String StringCreate(char* lit);

/*
 * StringResize
 * mengubah ukuran container string. Jika nilai container kurang dari panjang string
   maka string akan terpotong dan panjangnya menyesuaikan.
 * string* str : pointer string yang ingin dirubah ukuran containernya
 * uint size : ukuran container
 */
void StringResize(String *str, uint size);

/*
 * StringLength
 * berfungsi untuk mendapatkan panjang string. Length akan mengambil nilai unsigned
   int 4 byte sebelum pointer string yang menyatakan panjang string.
 * string str : string yang ingin didapatkan panjangnya
 * return : uint yang menyatakan panjang string
 */
uint StringLength(String str);

/*
 * StringSize
 * berfungsi untuk mendapatkan ukuran container string. size akan mengambil nilai
   uint 7 byte sebelum pointer string yang menyatakan ukuran containernya
 * string str : string yang ingin didapatkan ukuran containernya.
 * return : uint yang menyatakan ukuran container
 */
uint StringSize(String str);

/*
 * StringAppendChar
 * berfungsi untuk menambah karakter pada akhiran string. Jika container tidak cukup
   menampung, maka akan dibuat string baru yang ukurannya 150% dari ukuran container
   sebelumnya.
 * string *str : pointer ke string yang ingin ditambahkan karakternya
 * char c : karakter yang dimaksud
 */
void StringAppendChar(String *str, char c);

/*
 * StringAppendString
 * berfungsi untuk menambah string pada akhiran string. Jika container tidak cukup
   menampung, maka akan dibuat string baru yang ukurannya 150% dari ukuran container
   sebelumnya.
 * string *str : pointer ke string yang ingin ditambahkan dengan string lain
 * string s : string yang ingin ditambahkan
 */
void StringAppendString(String *str, String s);

/*
 * StringEquals
 * berfungsi untuk menentukan apakah string s1 sama dengan string s2
 * string s1 : string pertama yang ingin dibandingkan
 * string s2 : string kedua yang ingin dibandingkan
 * return : boolean yang menyatkaan sama atau tidak
 */
boolean StringEquals(String s1, String s2);

/*
 * StringReadln
 * membaca satu baris string dari stdio
 * string *str : pointer yang menyatakan tempat menampung string yang dibaca
 * return : int yang menyatakan kode ascii karakter terakhir yang dibaca
 */
int StringReadln(String *str);

/*
 * StringFreadln
 * membaca satu baris string dari file
 * string *str : pointer yang menyatakan tempat menampung string yang dibaca
 * FILE *f : pointer ke file yang ingin dibaca
 * return : int yang menyatakan kode ascii karakter terakhir yang dibaca
 */
int StringFreadln(String *str, FILE *f);

#endif
