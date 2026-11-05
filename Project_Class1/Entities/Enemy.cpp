#include "Enemy.h"
#include <cassert>

void Enemy::onUpdate(float dt)
{
	Character* target = m_world->nearestPlayer(getCenter());
	if (target == nullptr)
	{
		return;
	}
	if (isDead()) 
	{
		destroy();
		return;
	}
	Vec2 unit{ target->getCenter() - getCenter() };
	unit.normalize();

	Vec2 delta = unit * dt * m_speed;//calculate the delta
	moveWithCollision(delta);

	if (getBounds().intersects(target->getBounds())) 
	{
		target->takeDamage(m_contactDamage);
	}
}

int Enemy::getContactDamage() const
{
	return m_contactDamage;
}

EntityType Enemy::getType() const
{
	return EntityType::Enemy;
}

void Enemy::saveKey(std::ostream& out) const 
{
	out << m_defIndex << ' ';
}
