#include "Player.h"
#include "../Core/Config.h"

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

	m_position += unit * dt * m_speed;//calculate the position

	//limit the position in the world range
	float endX = static_cast<float>(WORLD_WIDTH) - m_size.x;
	float endY = static_cast<float>(WORLD_HEIGHT) - m_size.y;
	if (m_position.x < 0)
		m_position.x = 0;
	if (m_position.x > endX)
		m_position.x = endX;
	if (m_position.y < 0)
		m_position.y = 0;
	if (m_position.y > endY)
		m_position.y = endY;
}