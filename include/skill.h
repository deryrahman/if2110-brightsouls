/*
Author
Nama 	: Dery Rahman A
NIM		: 13515097
Tanggal	: 13/11/2016
File	: skill.h
*/
#ifndef _SKILL_H
#define _SKILL_H
#include "boolean.h"
#include "integer.h"
#include <stdlib.h>

#define Nil NULL

typedef struct tSkill *SkillAddress;
typedef struct tSkill {
	uint attack;
	uint deffense;
} Skill;

#define Attack(X) (X).attack
#define Deffense(X) (X).deffense

Skill SkillCreate(uint X, uint Y);
void SkillMake(Skill *skill, uint X, uint Y);
#endif