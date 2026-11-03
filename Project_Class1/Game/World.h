#pragma once
#include "../Core/DynamicArray.h"
#include "../Entities/Entity.h"

class Renderer;
class Camera;

class World
{
public:
	World() = default;
	World(const World& source) = delete;
	World& operator=(const World& source) = delete;
	~World();

	void add(Entity* e);
	void update(float dt);
	void draw(Renderer&, const Camera&) const;
	int getCount() const;
	bool loadfromfile() const;//reserved
	bool damageArea(const Rect& area, int damage, Team attacker);
	Entity* findById(int id) const;
	int selectHighestHp(Vec2 center, float range, Team attacker, int* outIds, int n) const;
	void clear();
	int getScore() const;
	int getKills() const;

	//for S/L
	void addWithId(Entity* e, int id);
	Entity* getAt(int i) const;
	void setStats(int score, int kills);

private:
	DynamicArray<Entity*> m_entities{};
	int m_nextId{ 0 };
	int m_score{ 0 };
	int m_kills{ 0 };

	void removeDead();//World determines when to remove
};
