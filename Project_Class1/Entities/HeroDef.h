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

//HeroDef struct, used to define the properties of a hero type, including size, hitbox, texture, health, speed, attack damage, attack box, attack cooldown, shooting projectile, shooting cooldown, skill type, skill cooldown, skill duration, skill magnitude, magic projectile, maximum mana, skill mana cost, and mana regeneration
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
	float maxMana{};
	float skillManaCost{};
	float manaRegen{};
};