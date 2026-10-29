#pragma once
#include "Entity.h"
#include <cassert>

class Character : public Entity
{
public:
	

	void takeDamage(int damage);
	void heal(int healValue);
	bool isDead() const;
	int getHp() const;
	int getMaxHp() const;

protected:
	Character(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, int maxHp)
		:Entity(pos, size, tex)
		, m_hp{ maxHp }
		, m_maxHp{ maxHp }
	{
		assert(maxHp > 0 && "hp must be positive");
	}

private:
	int m_hp{};
	int m_maxHp{};
};