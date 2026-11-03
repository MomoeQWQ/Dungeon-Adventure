#pragma once
#include "Character.h"
#include "ProjectileDef.h"
#include "../Game/World.h"
#include <cassert>

class Turret:public Character
{
public:
	Turret(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, int maxHp, const Tilemap* map, World* world, ProjectileDef* shot,
		float interval,float range,int targetId)
		: Character(pos,size,tex,maxHp,map)
		, m_world{world}
		, m_shot{shot}
		, m_interval{interval}
		, m_range{range}
		, m_targetId{targetId}
	{
		m_timer = interval;
		m_team = Team::Enemy;
		assert(world != nullptr && "nullptr world cannot be used to initialize a Turret");
		assert(interval > 0.0f && "interval cannot be zero or minus");
	}

	EntityType getType() const override;

	void saveKey(std::ostream& out) const override;

	void save(std::ostream& out) const override;

	void load(std::istream& in) override;

private:
	World* m_world{};
	const ProjectileDef* m_shot;
	float m_interval;
	float m_timer{0.0f};
	float m_range;
	int m_targetId;


	void onUpdate(float dt) override;
};