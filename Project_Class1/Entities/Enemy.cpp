#include "Enemy.h"
#include "Entity.h"
#include <cassert>
#include <iostream>

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

	//separation behavior
	Vec2 c = getCenter();
	Rect queryRect{ c.x - kSeparationRadius, c.y - kSeparationRadius, kSeparationRadius * 2.0f, kSeparationRadius * 2.0f };
	Entity* nearby[32]{};
	int n = m_world->queryArea(queryRect, nearby, 32);
	Vec2 push{ 0, 0 };
	for (int i = 0; i < n; ++i)
	{
		Entity* e = nearby[i];
		if (e == this || e->getType() != EntityType::Enemy)
		{
			continue;
		}
		Vec2 diff = c - e->getCenter();
		float len = diff.length();
		if (len < kSeparationRadius && len > 0.0001f)
		{
			diff.normalize();
			push += diff * ((kSeparationRadius - len) / kSeparationRadius);
		}
		moveWithCollision(push * kSeparationStrength * dt);
	}


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
