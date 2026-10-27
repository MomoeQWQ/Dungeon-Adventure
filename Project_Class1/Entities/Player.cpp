#include "Player.h"

void Player::update(float dt) 
{
	Vec2 unit{ 0.0f,0.0f };
	if (m_input->isDown('W'))
		unit += Vec2{ 0.0f,-1.0f };
	if (m_input->isDown('A'))
		unit += Vec2{ -1.0f,0.0f };
	if (m_input->isDown('S'))
		unit += Vec2{ 0.0f,1.0f };
	if (m_input->isDown('D'))
		unit += Vec2{ 1.0f,0.0f };
	unit.normalize();

	Vec2 delta = unit * dt * m_speed;//calculate the delta

	float oldX = m_position.x;
	m_position.x += delta.x;
	if (m_map->isAreaBlocked(getBounds()))
		m_position.x = oldX;

	float oldY = m_position.y;
	m_position.y += delta.y;
	if (m_map->isAreaBlocked(getBounds()))
		m_position.y = oldY;
}