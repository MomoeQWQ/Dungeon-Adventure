#pragma once
#include "Entity.h"
#include "../Game/Tilemap.h"
#include "Player.h"
#include <cassert>

class Door : public Entity
{
public:
	Door(int col, int row, Tilemap* map, Player* target)
		:Entity(Vec2{ static_cast<float>(col * 32 - 8), static_cast<float>(row * 32 - 8) }, Vec2{ 48, 48 }, nullptr)
		,m_map{map}
		,m_target{target}
		,m_col{col}
		,m_row{row}
	{
		assert(map != nullptr && "map cannot be nullptr to init a door");
		assert(target != nullptr && "target cannot be nullptr to init a door");
		m_map->setTile(m_col, m_row, TileType::Door);
	}

	void update(float dt) override;

private:
	Tilemap* m_map{};
	Player* m_target{};
	int m_col{};
	int m_row{};
	bool m_open{ false };
};