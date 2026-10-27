#pragma once
#include "Entity.h"
#include "../Game/Input.h"
#include <cassert>

class Player : public Entity
{
public:
	Player(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex,const Input* input)
		:Entity{pos,size,tex}
		,m_input{input}
	{
		assert(input != nullptr && "nullptr input cannot be accepted to create a Player!");
	}

	void update(float dt) override;

private:
	const Input* m_input{};
	float m_speed{200.0f};
};

