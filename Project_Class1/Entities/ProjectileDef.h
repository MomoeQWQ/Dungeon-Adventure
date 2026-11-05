#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/Vec2.h"

//ProjectileDef struct, used to define the properties of a projectile type, including size, texture, speed, damage, and lifetime
struct ProjectileDef
{
	Vec2 size{};
	const GamesEngineeringBase::Image* tex{};
	float speed{};
	int damage{};
	float lifetime{};
};