#pragma once
#include "Character.h"
#include "../Game/Input.h"
#include "../Core/Rect.h"
#include "../Core/Vec2.h"
#include <cassert>

class World;

class Player : public Character
{
public:
	Player(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, int maxHp, const Tilemap* map, const Input* input, World* world)
		:Character{pos,size,tex,maxHp,map}
		,m_input{input}
		,m_world{world}
		
	{
		assert(input != nullptr && "nullptr input cannot be accepted to create a Player!");
		assert(world != nullptr && "nullptr world cannot be accepted to create a Player!");
		m_hitboxOffset = Vec2{ kHitboxOffsetX ,kHitboxOffsetY };
		m_hitboxSize = Vec2{ kHitboxSizeX ,kHitboxSizeY };
		m_team = Team::Player;
	}

	Rect m_range{};

private:
	const Input* m_input{};
	float m_speed{200.0f};
	World* m_world{};
	int m_meleeDamage{ 10 };
	Vec2 m_attackbox{ 40.0f,40.0f };
	Vec2 m_facing{1.0f,0.0f};
	static constexpr float kHitboxOffsetX{ 39.0f };
	static constexpr float kHitboxOffsetY{ 49.0f };
	static constexpr float kHitboxSizeX{ 31.0f };
	static constexpr float kHitboxSizeY{ 37.0f };//due to png picture

	void onUpdate(float dt) override;
};

