#pragma once
#include "../GamesEngineeringBase.h"
#include "Entity.h"
#include "../Core/Vec2.h"
#include <cassert>

class Tilemap;
class World;

//Projectile class, derived from Entity, represents a projectile entity in the game that can be fired by players or enemies
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
		, m_speed{velocity.length()}//we need m_speed to keep speed in magic bullet(direction changes every frame)
	{
		assert(map != nullptr && "nullptr map cannot be accepted to create a Projectile!");
		assert(world != nullptr && "nullptr world cannot be accepted to create a Projectile!");
		m_team = team;
	}

	void update(float dt) override;
	void setTarget(int id);

	EntityType getType() const override;

private:
	int m_targetId{ -1 };
	Vec2 m_velocity{};
	int m_damage{};
	float m_lifetime{};
	const Tilemap* m_map{};
	World* m_world{};
	float m_speed{};
};
