#pragma once
#include "Character.h"
#include "EnemyDef.h"

class Enemy : public Character
{
public:
	Enemy (Vec2 pos, const Tilemap* map, Character* target, const EnemyDef& def);
	int getContactDamage() const;

private:
	Character* m_target{};
	float m_speed{};
	int m_contactDamage{};

	void onUpdate(float dt) override;
};
