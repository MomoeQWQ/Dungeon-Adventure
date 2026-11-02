#include "Turret.h"
#include "Entity.h"
#include "Projectile.h"

void Turret::onUpdate(float dt) 
{
	m_timer -= dt;
	if (m_timer > 0.0f)
		return;
	if (m_world->findById(m_targetId) == nullptr)
		return;
	Entity* target = m_world->findById(m_targetId);
	float dx = target->getCenter().x - getCenter().x;
	float dy = target->getCenter().y - getCenter().y;
	if (m_range < dx * dx + dy * dy)
		return;
	Vec2 unit{ Vec2{ dx, dy }.normalized() };
	m_world->add(new Projectile{ getCenter() - m_shot->size * 0.5f,m_shot->size,m_shot->tex, unit * m_shot->speed,m_shot->damage,m_team,m_shot->lifetime,getMap(),m_world });
	m_timer = m_interval;
}