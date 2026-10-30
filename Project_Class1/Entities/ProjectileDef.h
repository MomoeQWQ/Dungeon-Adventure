#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/Vec2.h"

struct ProjectileDef
{
	Vec2 size{};
	const GamesEngineeringBase::Image* tex{};
	float speed{};
	int damage{};
	float lifetime{};
};