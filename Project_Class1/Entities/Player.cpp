#include "Player.h"
#include "Projectile.h"
#include "../Render/Renderer.h"
#include "../Game/World.h"

Projectile* Player::spawnProjectile(const ProjectileDef& def) const 
{
	return new Projectile{ getCenter() - def.size * 0.5f,def.size,def.tex,m_facing * def.speed,def.damage,m_team,def.lifetime,getMap(),m_world };
}

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

	//in-built timer
	m_shootCooldown = std::max(0.0f, m_shootCooldown - dt);
	m_magicCooldown = std::max(0.0f, m_magicCooldown - dt);

	//shoot
	if (m_input->wasPressed('K')&& m_shootCooldown <= 0.0f)
	{
			m_world->add(spawnProjectile(*m_projDef));
			m_shootCooldown = kShootCooldown;
	}

	//magic
	if (m_input->wasPressed('L')&& m_magicCooldown <= 0.0f)
	{
		int ids[kMagicTargets]{};
		int count = m_world->selectHighestHp(getCenter(), kMagicRange, m_team, ids, kMagicTargets);
		for (int i = 0;i < count;i++) 
		{
			Projectile* p = spawnProjectile(*m_magicDef);
			p->setTarget(ids[i]);
			m_world->add(p);
		}
		if (count > 0) 
			m_magicCooldown = kMagicCooldown;
	}
}