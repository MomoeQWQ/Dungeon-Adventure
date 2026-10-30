#include "Player.h"
#include "../Render/Renderer.h"
#include "../Game/World.h"

void Player::onUpdate(float dt)
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
	
	if (unit.length() >= 0.0001f)
	{
		unit.normalize();
		m_facing = unit;
		Vec2 delta = unit * dt * m_speed;//calculate the delta

		moveWithCollision(delta);
	}

	//attack
	if (m_input->wasPressed('J'))
	{
		Vec2 cPoint{ getCenter()};
		cPoint += Vec2{ m_facing.x * (m_attackbox.x + m_hitboxSize.x) / 2 ,m_facing.y * (m_attackbox.y + m_hitboxSize.y) / 2 };
		Vec2 attackTopLeftPoint{ cPoint - Vec2{ m_attackbox.x / 2,m_attackbox.y / 2 } };
		m_range = { attackTopLeftPoint.x,attackTopLeftPoint.y,m_attackbox.x,m_attackbox.y };
		m_world->damageArea(m_range, m_meleeDamage, m_team);
	}
}