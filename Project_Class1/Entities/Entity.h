#pragma once
#include "../Core/Vec2.h"
#include "../GamesEngineeringBase.h"
#include "../Render/Renderer.h"
#include "../Render/Camera.h"
#include "../Core/Rect.h"
#include "EntityType.h"
#include <iosfwd>

enum class Team
{
	Neutral = 0,//default
	Player,
	Enemy
};

//Base class for all entities in the game, including Characters, projectiles, doors, etc.
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

	virtual void onHit(int damage);

	Team getTeam() const;

	int getId() const;

	void setId(int id);//only class world is permitted to use this function

	virtual int getHp() const { return 0; }

	virtual int getScoreValue() const { return 0; }

	virtual void onTriggered() {}

	//function below is added to support S/L
	virtual EntityType getType() const = 0;

	virtual void saveKey(std::ostream& out) const {}

	virtual void save(std::ostream& out) const;

	virtual void load(std::istream& in);

	//for Broadphase, avoid using the same entity in one query
	friend class World;

protected:
	Entity(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex)
		:m_position{ pos }
		, m_size{ size }
		, m_texture{ tex }
		, m_hitboxSize{ size }
	{
	}

	int m_id{-1};
	Vec2 m_position{};
	Vec2 m_size{};
	const GamesEngineeringBase::Image* m_texture{};
	Vec2 m_hitboxOffset{};
	Vec2 m_hitboxSize{ m_size };
	bool m_isAlive{ true };
	int m_srcX{0};
	int m_srcY{0};
	Team m_team{ Team::Neutral };

private:
	mutable int m_lastQuery{ -1 };
};