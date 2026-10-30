#pragma once
#include "../GamesEngineeringBase.h"
#include "Entity.h"
#include "../Core/Vec2.h"
#include <cassert>

class Tilemap;
class World;

class Projectile : public Entity
{
public:
	Projectile(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, Vec2 velocity, int damage, Team team, float lifetime, const Tilemap* map, World* world)
		:Entity(pos,size,tex)
		, m_velocity{velocity}
		, m_damage{damage}
		, m_lifetime{lifetime}
		, m_map{map}
		, m_world{world}
	{
		assert(map != nullptr && "nullptr map cannot be accepted to create a Projectile!");
		assert(world != nullptr && "nullptr world cannot be accepted to create a Projectile!");
		m_team = team;
	}

	void update(float dt) override;

private:
	Vec2 m_velocity{};
	int m_damage{};
	float m_lifetime{};
	const Tilemap* m_map{};
	World* m_world{};
};
