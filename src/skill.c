#include <stdio.h>
#include "../include/skill.h" // masih dijalankan terpisah dari main utama

Skill SkillCreate(uint X, uint Y){
	Skill P;
	Attack(P)=X;
	Deffense(P)=Y;
	return P;
}

void SkillMake(Skill *skill, uint X, uint Y){
	*skill=SkillCreate(X,Y);
}