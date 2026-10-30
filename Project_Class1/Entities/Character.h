#pragma once
#include "Entity.h"
#include "../Game/Tilemap.h"
#include <cassert>

class Character : public Entity
{
public:
	
	void takeDamage(int damage);
	void heal(int healValue);
	bool isDead() const;
	int getHp() const;
	int getMaxHp() const;

	void update(float dt) override final;
	bool isInvulnerable() const;
	
protected:
	Character(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, int maxHp, const Tilemap* map)
		:Entity(pos, size, tex)
		, m_hp{ maxHp }
		, m_maxHp{ maxHp }
		, m_map{ map }
	{
		assert(maxHp > 0 && "hp must be positive");
		assert(map != nullptr && "nullptr map cannot be accepted to create a Character!");
	}

	void moveWithCollision(Vec2 delta);//shared by Player and Enemy
	const Tilemap* getMap() const;

private:
	static constexpr float kInvulnDuration{ 0.8f };
	int m_hp{};
	int m_maxHp{};
	const Tilemap* m_map{};
	float m_invulnTimer{ kInvulnDuration };//born protection

	virtual void onUpdate(float dt) = 0;//NVI hook
};