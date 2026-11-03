#pragma once
#include "../Game/Input.h"
#include "../Core/Rect.h"
#include "../Core/Vec2.h"
#include "Character.h"
#include "HeroDef.h"
#include <cassert>

class World;
class Projectile;

class Player : public Character
{
public:
	Player(Vec2 pos, const Tilemap* map, const Input* input, World* world, const HeroDef& def)
		: Character{pos,def.size,def.tex,def.maxHp,map}
		, m_input{input}
		, m_world{world}
		, m_def{&def}
		, m_mana{def.maxMana}
	{
		assert(input != nullptr && "nullptr input cannot be accepted to create a Player!");
		assert(world != nullptr && "nullptr world cannot be accepted to create a Player!");
		m_hitboxOffset = def.hitboxOffset;
		m_hitboxSize = def.hitboxSize;
		m_team = Team::Player;
	}

	Rect m_range{};

	void addMana(int);
	float getMana() const;
	float getMaxMana() const;

private:
	//player para
	const Input* m_input{};
	World* m_world{};
	const HeroDef* m_def{};
	Vec2 m_facing{ 1.0f,0.0f };
	float m_mana{};

	// Timer
	float m_meleeTimer{ 0.0f };
	float m_shootTimer{ 0.0f };
	float m_skillTimer{ 0.0f };
	float m_buffTimer{ 0.0f };

	//constexpr
	static constexpr float kMagicRange = 300.0f;
	static constexpr int kMagicTargets = 3;

	//onUpdate
	void onUpdate(float dt) override;

	//helper function
	Projectile* spawnProjectile(const ProjectileDef& def) const;
};

