#include "Character.h"
#include <algorithm>
#include <cassert>

void Character::takeDamage(int damage)
{
	assert(damage >= 0 && "a minus damage cannot be applied!");
	m_hp -= damage;
	m_hp = std::clamp(m_hp, 0, m_maxHp);
}

void Character::heal(int healValue)
{
	assert(healValue >= 0 && "a minus heal cannot be applied!");
	if (isDead())
		return;//designed to avoid reviving
	m_hp += healValue;
	m_hp = std::clamp(m_hp, 0, m_maxHp);
}

bool Character::isDead() const
{
	return (m_hp == 0);
}

int Character::getHp() const
{
	return m_hp;
}

int Character::getMaxHp() const
{
	return m_maxHp;
}