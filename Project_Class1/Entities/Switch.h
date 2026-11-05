#pragma once
#include "Entity.h"
#include "../Game/World.h"
#include "Player.h"
#include "../GamesEngineeringBase.h"
#include <cassert>

//Switch class, derived from Entity, represents a switch entity in the game that can be activated by the player to trigger certain actions in the game world
class Switch : public Entity
{
public:
	Switch(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* texOff, const GamesEngineeringBase::Image* texOn, World* world, Player* target)
		:Entity(pos, size, texOff)
		, m_texOff{ texOff }
		, m_texOn{ texOn }
		, m_world{ world }
		, m_target{ target }
	{
		assert(texOff != nullptr && "nullptr texOff used in init Switch");
		assert(texOn != nullptr && "nullptr texOn used in init Switch");
		assert(world != nullptr && "nullptr world used in init Switch");
		assert(target != nullptr && "nullptr target used in init Switch");
		m_team = Team::Neutral;
	}

	void update(float dt) override;
	void addTarget(int id);

	EntityType getType() const override;

	void save(std::ostream& out) const override;

	void load(std::istream& in) override;

private:
	static constexpr int kMaxTargets = 4;

	World* m_world;
	Player* m_target;
	int m_targetIds[kMaxTargets]{};
	int m_targetCount{ 0 };
	const GamesEngineeringBase::Image* m_texOff;
	const GamesEngineeringBase::Image* m_texOn;
	bool m_on{ false };
	bool m_wasTouching{ false };
};