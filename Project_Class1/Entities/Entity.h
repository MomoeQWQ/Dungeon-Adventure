#pragma once
#include "../Core/Vec2.h"
#include "../GamesEngineeringBase.h"
#include "../Render/Renderer.h"
#include "../Render/Camera.h"
#include "../Core/Rect.h"

class Entity
{
public:

	virtual ~Entity() = default;

	virtual void draw(Renderer& renderer, const Camera& camera) const;

	virtual void update(float dt) = 0;

	Rect getBounds() const;

	Vec2 getCenter() const;

	bool isAlive() const;

	void destroy();



protected:
	Entity(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex)
		:m_position{ pos }
		, m_size{ size }
		, m_texture{ tex }
	{
	}

	Vec2 m_position{};
	Vec2 m_size{};
	bool m_isAlive{ true };
	const GamesEngineeringBase::Image* m_texture{};
	int m_srcX{0};
	int m_srcY{0};
};