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

	moveWithCollision(delta);
}