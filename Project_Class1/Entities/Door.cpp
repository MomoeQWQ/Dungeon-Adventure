#include "Door.h"

void Door::update(float dt) 
{
	if (m_open)
		return;
	if (getBounds().intersects(m_target->getBounds()) && m_target->useKey()) 
	{
		m_map->setTile(m_col, m_row, TileType::Road);
		m_open = true;
	}
}

EntityType Door::getType() const 
{
	return EntityType::Door;
}