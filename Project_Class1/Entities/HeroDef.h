#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/Vec2.h"
#include "ProjectileDef.h"
enum class SkillType
{
	Defence,
	Speed,
	Magic
};

struct HeroDef
{
	//appearance&tex
	Vec2 size{};
	Vec2 hitboxOffset{};
	Vec2 hitboxSize{};
	const GamesEngineeringBase::Image* tex{};
	int maxHp{};
	float speed{};

	//J:attack
	int meleeDamage{};
	Vec2 meleeBox{};
	float meleeCooldown{};

	//K:shoot
	const ProjectileDef* shot{};
	float shootCooldown{};

	//L:magic/combat art
	SkillType skill{};
	float skillCooldown{};
	float skillDuration{};
	float skillMagnitude{};
	const ProjectileDef* magic{};
};