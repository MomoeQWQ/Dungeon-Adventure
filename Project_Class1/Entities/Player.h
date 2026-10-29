#pragma once
#include "Character.h"
#include "../Game/Input.h"
#include <cassert>


class Player : public Character
{
public:
	Player(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, int maxHp, const Tilemap* map, const Input* input)
		:Character{pos,size,tex,maxHp,map}
		,m_input{input}
		
	{
		assert(input != nullptr && "nullptr input cannot be accepted to create a Player!");
		m_hitboxOffset = Vec2{ kHitboxOffsetX ,kHitboxOffsetY };
		m_hitboxSize = Vec2{ kHitboxSizeX ,kHitboxSizeY };
	}

	void update(float dt) override;

private:
	const Input* m_input{};
	float m_speed{200.0f};
	static constexpr float kHitboxOffsetX{ 39.0f };
	static constexpr float kHitboxOffsetY{ 49.0f };
	static constexpr float kHitboxSizeX{ 31.0f };
	static constexpr float kHitboxSizeY{ 37.0f };//due to png picture
};

