#include "Spawner.h"
#include "Enemy.h"
#include "../Game/World.h"
#include <iostream>

void Spawner::onUpdate(float dt)
{
	if (isDead()) 
	{
		return;//reserved but cannot spawn anymore
	}
	m_timer += dt;
	if (m_timer >= m_interval) 
	{
		m_world->add(new Enemy(m_position, getMap(), m_world, *m_def));
		m_timer -= m_interval;
	}
}

EntityType Spawner::getType() const
{
	return EntityType::Spawner;
}

void Spawner::saveKey(std::ostream& out) const
{
	out << m_def->index << ' ' << getMaxHp() << ' ' << m_interval << ' ';
}

void Spawner::save(std::ostream& out) const
{
	Character::save(out);
	out << m_timer << ' ';
}

void Spawner::load(std::istream& in)
{
	Character::load(in);
	in >> m_timer;
}