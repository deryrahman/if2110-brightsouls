/*
 * Author
 * Nama : Jauhar Arifin
 * Tanggal : Minggu, 11 September 2016
 * File : string.c
 */

#include "xstring.h"
#include "boolean.h"
#include "integer.h"
#include "stdlib.h"
#include "stdio.h"

/*
 * Implementasi str pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
String StringCreate(char* lit) {
	String baru = 0;
	StringResize(&baru, 0);

	while (*lit != 0)
		StringAppendChar(&baru, *(lit++));

	return baru;
}

/*
 * Implementasi resize pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
void StringResize(String *str, uint  sz) {
	void *all = (void*) malloc(sz + 9);

	uint *container = (uint*) all;
	uint *container_length = (uint*) (all + 4);
	String baru = all + 8;

	*container = sz;

	if (*str != 0) {
		uint n = StringLength(*str);
		uint i;
		for (i = 0; i < n && i < sz; i++)
			baru[i] = (*str)[i];
		baru[i] = '\0';
		*container_length = i;
		free(*str-8);
	} else {
		baru[0] = '\0';
		*container_length = 0;
	}

	*str = baru;
}

/*
 * Implementasi length pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
uint StringLength(String str) {
	if (str == 0)
		StringResize(&str, 0);
	void *p = (void*) str;
	p -= 4;
	uint *q = (uint*) p;
	return *q;
}

/*
 * Implementasi size pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
uint StringSize(String str) {
	if (str == 0)
		StringResize(&str, 0);
	void *p = (void*) str;
	p -= 8;
	uint *q = (uint*) p;
	return *q;
}

/*
 * Implementasi appendChar pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
void StringAppendChar(String *str, char c) {
	if (*str == 0)
		StringResize(str, 0);

	if (StringLength(*str) >= StringSize(*str))
		StringResize(str, ((StringSize(*str) + 1) * 3)/2);

	void *p = *str;
	uint *l = (uint*) (p - 4);
	*(*str + StringLength(*str)) = c;
	(*l)++;
	*(*str + StringLength(*str)) = '\0';
}

/*
 * Implementasi appendString pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
void StringAppendString(String *str, String s) {
	uint i;
	for (i = 0; i < StringLength(s); i++)
		StringAppendChar(str, s[i]);
}

/*
 * Implementasi equals pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
boolean StringEquals(String s1, String s2) {
	if (StringLength(s1) != StringLength(s2))
		return false;

	uint i;
	for (i = 0; i < StringLength(s1); i++)
		if (s1[i] != s2[i])
			return false;

	return true;
}

/*
 * Implementasi readln pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
int StringReadln(String *str) {
	StringResize(str, 0);

	uint i;
	char x;
	for (i = 0; x != '\n' && x != '\r'; i++) {
		x = (char) getchar();
		if (x != '\n' && x != '\r' && x != EOF)
			StringAppendChar(str, x);
	}

	return x;
}

/*
 * Implementasi freadln pada string.h
 * Tanggal : Minggu, 11 September 2016
 */
int StringFreadln(String *str, FILE *f) {
	StringResize(str, 0);

	char x;
	for (x = 1; x != '\n' && x != '\r' && x != EOF;) {
		x = (char) fgetc(f);
		if (x != '\n' && x != '\r' && x != EOF)
			StringAppendChar(str, x);
	}

	return x;
}
