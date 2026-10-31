#include "Player.h"
#include "Projectile.h"
#include "../Render/Renderer.h"
#include "../Game/World.h"
#include <algorithm>

Projectile* Player::spawnProjectile(const ProjectileDef& def) const 
{
	return new Projectile{ getCenter() - def.size * 0.5f,def.size,def.tex,m_facing * def.speed,def.damage,m_team,def.lifetime,getMap(),m_world };
}

void Player::onUpdate(float dt)
{
	//in-built timer change
	m_meleeTimer = std::max(0.0f, m_meleeTimer - dt);
	m_shootTimer = std::max(0.0f, m_shootTimer - dt);
	m_skillTimer = std::max(0.0f, m_skillTimer - dt);
	m_buffTimer = std::max(0.0f, m_buffTimer - dt);

	//set damage scale(for Skill::Defence
	if (m_buffTimer > 0.0f && m_def->skill == SkillType::Defence)
		setDamageScale(m_def->skillMagnitude);
	else
		setDamageScale(1.0f);

	//move
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
		bool isBuffed = m_buffTimer > 0 && m_def->skill == SkillType::Speed;
		float speed = m_def->speed * (isBuffed ? m_def->skillMagnitude : 1.0f);
		Vec2 delta = unit * dt * speed;//calculate the delta

		moveWithCollision(delta);//use move method in Character
	}

	//attack
	if (m_input->wasPressed('J')&& m_meleeTimer <= 0.0f)
	{
		Vec2 cPoint{ getCenter()};
		cPoint += Vec2{ m_facing.x * (m_def->meleeBox.x + m_hitboxSize.x) / 2 ,m_facing.y * (m_def->meleeBox.y + m_hitboxSize.y) / 2 };
		Vec2 attackTopLeftPoint{ cPoint - Vec2{ m_def->meleeBox.x / 2,m_def->meleeBox.y / 2 } };
		m_range = { attackTopLeftPoint.x,attackTopLeftPoint.y,m_def->meleeBox.x,m_def->meleeBox.y };
		m_world->damageArea(m_range, m_def->meleeDamage, m_team);
		m_meleeTimer = m_def->meleeCooldown;
	}

	//shoot
	if (m_input->wasPressed('K')&& m_shootTimer <= 0.0f)
	{
		assert(m_def->shot != nullptr);
		m_world->add(spawnProjectile(*m_def->shot));
		m_shootTimer = m_def->shootCooldown;
	}

	//magic
	if (m_input->wasPressed('L')&& m_skillTimer <= 0.0f)
	{
		switch (m_def->skill) 
		{
			case SkillType::Defence: 
			{
				m_buffTimer = m_def->skillDuration;
				m_skillTimer = m_def->skillCooldown;
				break;
			}
		
			case SkillType::Speed: 
			{
				m_buffTimer = m_def->skillDuration;
				m_skillTimer = m_def->skillCooldown;
				break;
			}

			case SkillType::Magic:
			{
				assert(m_def->magic != nullptr);
				int ids[kMagicTargets]{};
				int count = m_world->selectHighestHp(getCenter(), kMagicRange, m_team, ids, kMagicTargets);
				for (int i = 0;i < count;i++)
				{
					Projectile* p = spawnProjectile(*m_def->magic);
					p->setTarget(ids[i]);
					m_world->add(p);
				}
				if (count > 0)
					m_skillTimer = m_def->skillCooldown;
				break;
			}
		}
	}
}