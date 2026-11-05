#include "Door.h"
#include <iostream>

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

void Door::saveKey(std::ostream& out) const
{
	out << m_col << ' ' << m_row << ' ';
}

void Door::save(std::ostream& out) const
{
	Entity::save(out);
	out << m_open << ' ';
}

void Door::load(std::istream& in)
{
	Entity::load(in);
	in >> m_open;
	//door will be set tp door when loading, so if it's open, we need to set it to road
	if (m_open) 
	{
		m_map->setTile(m_col, m_row, TileType::Road);
	}
}