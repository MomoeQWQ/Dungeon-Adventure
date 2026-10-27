#include "Entity.h"

void Entity::draw(Renderer& renderer, const Camera& camera) const 
{
	if (m_texture == nullptr)
		return;
	Vec2 screenPos = camera.worldToScreen(m_position);
	renderer.drawImage(*m_texture, static_cast<int>(screenPos.x), static_cast<int>(screenPos.y),m_srcX,m_srcY,m_size.x,m_size.y);
}

Rect Entity::getBounds() const 
{
	return Rect{ m_position.x, m_position.y,m_size.x,m_size.y };
}

Vec2 Entity::getCenter() const
{
	return Vec2{ m_position.x + m_size.x / 2.0f,m_position.y + m_size.y / 2.0f };
}

bool Entity::isAlive() const
{
	return m_isAlive;
}

void Entity::destroy()
{
	m_isAlive = false;
}