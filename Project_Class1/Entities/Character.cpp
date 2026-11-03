#include "Character.h"
#include <algorithm>
#include <cassert>

void Character::takeDamage(int damage)
{
	assert(damage >= 0 && "a minus damage cannot be applied!");
	if (m_invulnTimer > 0)
		return;//character is in i-frames
	damage = static_cast<int>(damage * m_damageScale);
	m_hp -= damage;
	m_hp = std::clamp(m_hp, 0, m_maxHp);
	m_invulnTimer = kInvulnDuration;
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

void Character::moveWithCollision(Vec2 delta)
{
	float oldX = m_position.x;
	m_position.x += delta.x;
	if (m_map->isAreaBlocked(getBounds()))
		m_position.x = oldX;

	float oldY = m_position.y;
	m_position.y += delta.y;
	if (m_map->isAreaBlocked(getBounds()))
		m_position.y = oldY;
}

void Character::update(float dt)
{
	m_invulnTimer -= dt;
	m_invulnTimer = std::max(0.0f, m_invulnTimer);
	onUpdate(dt);//NVI,since every character should have i-frames
}

bool Character::isInvulnerable() const
{
	return m_invulnTimer > 0.0f;
}

void Character::onHit(int damage)
{
	takeDamage(damage);
}

const Tilemap* Character::getMap() const
{
	return m_map;
}

void Character::draw(Renderer& renderer, const Camera& camera) const
{
	if (isInvulnerable()) 
	{
		if (static_cast<int>(m_invulnTimer * 10) % 2 == 0)
			return;//blink when invulnerable
	}
	Entity::draw(renderer, camera);
}

void Character::setDamageScale(float scale)
{
	m_damageScale = scale;
}

void Character::save(std::ostream& out) const 
{
	Entity::save(out);
	out << m_hp << ' ' << m_invulnTimer << ' ';
}

void Character::load(std::istream& in) 
{
	Entity::load(in);
	in >> m_hp >> m_invulnTimer;
}