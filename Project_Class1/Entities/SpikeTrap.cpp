#include "SpikeTrap.h"

void SpikeTrap::update(float dt)
{
	if (!m_active)
		return;
	if (getBounds().intersects(m_target->getBounds()))
		m_target->takeDamage(m_damage);
}

void SpikeTrap::draw(Renderer& renderer, const Camera& camera) const
{
	if (!m_active)
		return;
	Entity::draw(renderer, camera);
}

void SpikeTrap::onTriggered()
{
	m_active = !m_active;
}

EntityType SpikeTrap::getType() const
{
	return EntityType::Spike;
}