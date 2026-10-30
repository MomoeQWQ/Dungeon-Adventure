#include "Entity.h"

void Entity::draw(Renderer& renderer, const Camera& camera) const 
{
	if (m_texture == nullptr)
		return;
	Vec2 screenPos = camera.worldToScreen(m_position);
	renderer.drawImage(*m_texture, static_cast<int>(screenPos.x), static_cast<int>(screenPos.y),m_srcX,m_srcY, static_cast<int>(m_size.x), static_cast<int>(m_size.y));
}

Rect Entity::getBounds() const 
{
	return Rect{ (m_position+m_hitboxOffset).x,(m_position + m_hitboxOffset).y,m_hitboxSize.x,m_hitboxSize.y };
}

Vec2 Entity::getCenter() const
{
	Rect bounds = getBounds();
	return Vec2{ bounds.x + bounds.w / 2.0f,bounds.y + bounds.h / 2.0f};
}

bool Entity::isAlive() const
{
	return m_isAlive;
}

void Entity::destroy()
{
	m_isAlive = false;
}

void Entity::onHit(int damage) 
{}//default:do nothing

Team Entity::getTeam() const 
{
	return m_team;
}