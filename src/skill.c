/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 13/11/2016
File	: skill.h
*/

#include <stdio.h>
#include "tree.h"
#include "skill.h" // masih dijalankan terpisah dari main utama

Skill SkillCreate(uint X, uint Y, uint lvl_req, uint urutan, String nama){
	Skill P;
	Attack(P)=X;
	Deffense(P)=Y;
	LVL(P)=lvl_req;
	Urutan(P)=urutan;
	Nama(P)=nama;
	return P;
}

void SkillMake(Skill *skill, uint X, uint Y, uint lvl_req, uint urutan, String nama){
	*skill=SkillCreate(X,Y,lvl_req,urutan,nama);
}
