#pragma once
#include"Entity.h"
#include"Character.h"
#include"../Core/Vec2.h"

class SpikeTrap : public Entity
{
public:
	SpikeTrap(Vec2 pos, Vec2 size, const GamesEngineeringBase::Image* tex, Character* target, int damage, bool active)
		:Entity(pos,size,tex)
		,m_target{target}
		,m_damage{damage}
		,m_active{active}
	{}
	
	void update(float dt) override;
	void draw(Renderer& renderer, const Camera& camera) const override;
	void setActive(bool) {};//reserved
	virtual void onTriggered() override;

private:
	Character* m_target{};
	int m_damage;
	bool m_active{ true };
};