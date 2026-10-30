#include "Enemy.h"
#include <cassert>

void Enemy::onUpdate(float dt)
{
	if (isDead()) 
	{
		destroy();
		return;
	}
	Vec2 unit{ m_target->getCenter() - getCenter() };
	unit.normalize();

	Vec2 delta = unit * dt * m_speed;//calculate the delta
	moveWithCollision(delta);

	if (getBounds().intersects(m_target->getBounds())) 
	{
		m_target->takeDamage(m_contactDamage);
	}
}

int Enemy::getContactDamage() const
{
	return m_contactDamage;
}