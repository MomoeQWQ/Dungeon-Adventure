#pragma once
#include "Character.h"
#include "../Game/Input.h"
#include "../Core/Rect.h"
#include "../Core/Vec2.h"
#include "ProjectileDef.h"
#include <cassert>

class World;
class Projectile;

class Player : public Character
{
public:
	Player(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, int maxHp, const Tilemap* map, const Input* input, World* world, const ProjectileDef* projDef, const ProjectileDef* magicDef)
		:Character{pos,size,tex,maxHp,map}
		,m_input{input}
		,m_world{world}
		,m_projDef{projDef}
		,m_magicDef{magicDef}
	{
		assert(input != nullptr && "nullptr input cannot be accepted to create a Player!");
		assert(world != nullptr && "nullptr world cannot be accepted to create a Player!");
		assert(projDef != nullptr && "nullptr projDef cannot be accepted to create a Player!");
		assert(magicDef != nullptr && "nullptr magicDef cannot be accepted to create a Player!");
		m_hitboxOffset = Vec2{ kHitboxOffsetX ,kHitboxOffsetY };
		m_hitboxSize = Vec2{ kHitboxSizeX ,kHitboxSizeY };
		m_team = Team::Player;
	}

	Rect m_range{};

private:
	//player para
	const Input* m_input{};
	float m_speed{200.0f};
	World* m_world{};
	int m_meleeDamage{ 10 };
	Vec2 m_attackbox{ 40.0f,40.0f };
	Vec2 m_facing{1.0f,0.0f};

	// shoot para
	const ProjectileDef* m_projDef{};
	float m_shootCooldown{0.0f};

	// magic para
	const ProjectileDef* m_magicDef{};
	float m_magicCooldown{ 0.0f };

	//constexpr
	static constexpr float kHitboxOffsetX{ 39.0f };
	static constexpr float kHitboxOffsetY{ 49.0f };
	static constexpr float kHitboxSizeX{ 31.0f };
	static constexpr float kHitboxSizeY{ 37.0f };//due to png picture
	static constexpr float kShootCooldown{ 0.8f };
	static constexpr float kMagicCooldown = 3.0f;
	static constexpr float kMagicRange = 300.0f;
	static constexpr int kMagicTargets = 3;

	//onUpdate
	void onUpdate(float dt) override;

	//helper function
	Projectile* spawnProjectile(const ProjectileDef& def) const;
};

