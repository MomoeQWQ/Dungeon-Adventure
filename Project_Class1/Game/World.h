#pragma once
#include "../Core/DynamicArray.h"
#include "../Entities/Entity.h"

class Renderer;
class Camera;
class Character;

//World class, responsible for managing all entities in the game world, including adding, updating, drawing, and querying entities
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

	//for P2
	Character* nearestPlayer(Vec2 from) const;

	//for Broadphase
	int queryArea(const Rect& area, Entity** out, int maxOut) const;  
	void toggleGrid();
	bool isUsingGrid() const;

private:
	static constexpr int kMaxQuery = 256;
	static constexpr float kCellSize = 128.0f;
	static constexpr int kGridW = 64;
	static constexpr int kGridH = 64;
	static constexpr int kMaxPlayers = 2;

	DynamicArray<Entity*> m_entities{};
	DynamicArray<Entity*> m_cells[kGridW * kGridH];
	bool m_useGrid{ true };
	mutable int m_queryStamp{ 0 };
	int m_nextId{ 0 };
	int m_score{ 0 };
	int m_kills{ 0 };
	Character* m_players[kMaxPlayers]{};
	int m_playerCount{ 0 };
	
	void removeDead();//World determines when to remove
	static int cellIndex(int cx, int cy);
	void rebuildGrid();
};
