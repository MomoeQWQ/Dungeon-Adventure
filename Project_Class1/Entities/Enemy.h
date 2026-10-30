#pragma once
#include "Character.h"
#include "EnemyDef.h"

class Enemy : public Character
{
public:
	Enemy(Vec2 pos, const Tilemap* map, Character* target, const EnemyDef& def)
		:Character(pos, def.size, def.tex, def.maxHp, map)
		, m_target{ target }
		, m_speed{ def.speed }
		, m_contactDamage{ def.contactDamage }
	{
		assert(m_target != nullptr && "nullptr target cannot be accepted to create an Enemy!");
		m_hitboxOffset = def.hitboxOffset;
		m_hitboxSize = def.hitboxSize;
		m_team = Team::Enemy;
	}
	int getContactDamage() const;

private:
	Character* m_target{};
	float m_speed{};
	int m_contactDamage{};

	void onUpdate(float dt) override;
};
