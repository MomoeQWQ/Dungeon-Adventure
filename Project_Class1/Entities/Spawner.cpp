#include "Spawner.h"
#include "Enemy.h"
#include "../Game/World.h"

void Spawner::onUpdate(float dt)
{
	if (isDead()) 
	{
		return;//reserved but cannot spawn anymore
	}
	m_timer += dt;
	if (m_timer >= m_interval) 
	{
		m_world->add(new Enemy(m_position, getMap(), m_target, *m_def));
		m_timer -= m_interval;
	}
}