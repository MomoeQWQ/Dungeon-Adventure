#pragma once
#include "Entity.h"
#include "../Game/Input.h"
#include "../Game/Tilemap.h"
#include <cassert>


class Player : public Entity
{
public:
	Player(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex,const Input* input, const Tilemap* map)
		:Entity{pos,size,tex}
		,m_input{input}
		, m_map{map}
	{
		assert(input != nullptr && "nullptr input cannot be accepted to create a Player!");
		assert(map != nullptr && "nullptr map cannot be accepted to create a Player!");
		m_hitboxOffset = Vec2{ kHitboxOffsetX ,kHitboxOffsetY };
		m_hitboxSize = Vec2{ kHitboxSizeX ,kHitboxSizeY };
	}

	void update(float dt) override;

private:
	const Input* m_input{};
	const Tilemap* m_map{};
	float m_speed{200.0f};
	static constexpr float kHitboxOffsetX{ 39.0f };
	static constexpr float kHitboxOffsetY{ 49.0f };
	static constexpr float kHitboxSizeX{ 31.0f };
	static constexpr float kHitboxSizeY{ 37.0f };//due to png picture
};

