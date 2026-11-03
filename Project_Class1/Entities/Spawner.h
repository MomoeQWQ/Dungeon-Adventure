#pragma once
#include "Character.h"
#include "EnemyDef.h"
#include <cassert>

class World;

class Spawner : public Character
{
public:
	Spawner(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, int maxHp, const Tilemap* map, World* world, Character* target, const EnemyDef* def, float interval) 
		: Character{ pos , size, tex, maxHp, map }
		, m_world{world}
		, m_target{target}
		, m_def{def}
		, m_interval{interval}
	{
		assert(world != nullptr && "nullptr world cannot be used to initialize a Spawner");
		assert(target != nullptr &&"nullptr target cannot be used to initialize a Spawner");
		assert(def != nullptr &&"nullptr def cannot be used to initialize a Spawner");
		assert(interval > 0.0f && "interval cannot be zero or minus");
		m_team = Team::Enemy;
	}

	EntityType getType() const override;

	void saveKey(std::ostream& out) const override;

	void save(std::ostream& out) const override;

	void load(std::istream& in) override;

private:
	World* m_world{};
	Character* m_target{};
	const EnemyDef* m_def{};
	float m_interval{};
	float m_timer{0.0f};

	void onUpdate(float dt) override;
};