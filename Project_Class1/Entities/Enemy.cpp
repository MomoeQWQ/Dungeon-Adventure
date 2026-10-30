#include "Enemy.h"
#include <cassert>

Enemy::Enemy(Vec2 pos, const Tilemap* map, Character* target, const EnemyDef& def)
	:Character(pos,def.size,def.tex,def.maxHp,map)
	, m_target{target}
	, m_speed{def.speed}
	, m_contactDamage{def.contactDamage}
{
	assert(m_target != nullptr && "nullptr target cannot be accepted to create an Enemy!");
	m_hitboxOffset = def.hitboxOffset;
	m_hitboxSize = def.hitboxSize;
	m_team = Team::Enemy;
}

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