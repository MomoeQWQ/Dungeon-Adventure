#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/Vec2.h"

struct EnemyDef
{
	Vec2 size{};
	Vec2 hitboxOffset{};
	Vec2 hitboxSize{};
	const GamesEngineeringBase::Image* tex{};
	int maxHp{};
	int contactDamage{};
	float speed{};
};