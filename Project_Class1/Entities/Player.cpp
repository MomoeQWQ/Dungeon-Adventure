#include "Player.h"
#include "../Render/Renderer.h"
#include "../Game/World.h"
#include "Projectile.h"

constexpr float kShootCooldown{ 0.8f };

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

	//shoot
	m_shootCooldown -= dt;

	if (m_input->wasPressed('K'))
	{
		if (m_shootCooldown <= 0.0001f) {
			m_world->add(new Projectile{ getCenter() - m_projDef->size * 0.5f,m_projDef->size,m_projDef->tex,m_facing * m_projDef->speed,m_projDef->damage,m_team,m_projDef->lifetime,getMap(),m_world });
			m_shootCooldown = kShootCooldown;
		}	
	}
}