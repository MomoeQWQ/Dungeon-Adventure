#pragma once
#include "Character.h"
#include "EnemyDef.h"
#include "../Game/World.h"

//Enemy class, derived from Character, represents an enemy entity in the game
class Enemy : public Character
{
public:
	Enemy(Vec2 pos, const Tilemap* map, World* world, const EnemyDef& def)
		:Character(pos, def.size, def.tex, def.maxHp, map)
		, m_world{ world }
		, m_speed{ def.speed }
		, m_contactDamage{ def.contactDamage }
		, m_score{ def.score }
		, m_defIndex{def.index}
	{
		assert(m_world != nullptr && "nullptr world cannot be accepted to create an Enemy!");
		m_hitboxOffset = def.hitboxOffset;
		m_hitboxSize = def.hitboxSize;
		m_team = Team::Enemy;
	}

	int getContactDamage() const;
	int getScoreValue() const override { return m_score; };

	EntityType getType() const override;

	void saveKey(std::ostream& out) const override;

private:
	World* m_world{};
	float m_speed{};
	int m_contactDamage{};
	int m_score{};
	int m_defIndex{};

	static constexpr float kSeparationRadius = 40.0f;
	static constexpr float kSeparationStrength = 120.0f;

	void onUpdate(float dt) override;
};
