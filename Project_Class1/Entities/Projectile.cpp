#include "Entity.h"
#include "Projectile.h"
#include "../Game/Tilemap.h"
#include "../Game/World.h"
#include "../Core/Vec2.h"

void Projectile::update(float dt)
{
	if (m_targetId >= 0) 
	{
		Entity* targetPtr = m_world->findById(m_targetId);
		if (targetPtr == nullptr) 
		{
			m_targetId = -1;
		}
		else 
		{
			Vec2 dir = targetPtr->getCenter() - getCenter();
			if (dir.length() > 0.0001f) 
			{
				m_velocity = dir.normalized() * m_speed;
			}
		}
	}
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

void Projectile::setTarget(int id) 
{
	m_targetId = id;
}

EntityType Projectile::getType() const 
{
	return EntityType::Projectile;
}