#include "Projectile.h"
#include "../Game/Tilemap.h"
#include "../Game/World.h"

void Projectile::update(float dt)
{
	m_position += m_velocity * dt;
	m_lifetime -= dt;
	if (m_lifetime <= 0) 
	{
		destroy();
		return;
	}
	if (m_map->isAreaBlocked(getBounds())) 
	{
		destroy();
		return;
	}

	if (m_world->damageArea(getBounds(), m_damage, m_team))
		destroy();
}