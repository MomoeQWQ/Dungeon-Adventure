#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/Vec2.h"

//EnemyDef struct, used to define the properties of an enemy type, including size, hitbox, texture, health, damage, speed, score value, and index
struct EnemyDef
{
	Vec2 size{};
	Vec2 hitboxOffset{};
	Vec2 hitboxSize{};
	const GamesEngineeringBase::Image* tex{};
	int maxHp{};
	int contactDamage{};
	float speed{};
	int score{};
	int index{};
};