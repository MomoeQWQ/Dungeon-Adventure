#pragma once
#include "Entity.h"
#include "../Core/Vec2.h"
#include "Player.h"
#include <cassert>

enum class PickupType { Health, Mana, Key };

class Pickup : public Entity
{
public:
	Pickup(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, PickupType type,int amount, Player* target)
		:Entity(pos,size,tex)
		,m_type{type}
		,m_amount{amount}
		,m_target{target}
	{
		assert(m_target != nullptr && "nullptr target cannot be accepted to create a Pickup!");
		m_team = Team::Neutral;
	}

private:
	PickupType m_type{};
	int m_amount{};
	Player* m_target{};

	void update(float dt) override;
};