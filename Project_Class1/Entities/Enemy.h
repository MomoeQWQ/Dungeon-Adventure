#pragma once
#include "Character.h"
#include "EnemyDef.h"

class Enemy : public Character
{
public:
	Enemy (Vec2 pos, const Tilemap* map, const Character* target, const EnemyDef& def);
	void update(float dt) override;
	int getContactDamage() const;

private:
	const Character* m_target{};
	float m_speed{};
	int m_contactDamage{};
};
