#pragma once
#include"Entity.h"
#include"Character.h"
#include"../Core/Vec2.h"

//SpikeTrap class, derived from Entity, represents a spike trap entity in the game that can damage a target character when triggered
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

	EntityType getType() const override;

	void saveKey(std::ostream& out) const override;

	void save(std::ostream& out) const override;

	void load(std::istream& in) override;

private:
	Character* m_target{};
	int m_damage;
	bool m_active{ true };
};