#include "World.h"
#include "../Render/Renderer.h"
#include "../Render/Camera.h"
#include <cassert>

World::~World()
{
	for (int i = 0;i < m_entities.getSize();i++) 
	{
		delete m_entities[i];//World in charge of Entities's memory
	}
}

void World::add(Entity* e) 
{
	assert(e != nullptr && "enetity cannot be nullptr");
	m_entities.push_back(e);
}

void World::update(float dt) 
{
	for (int i = 0;i < m_entities.getSize();i++)
	{
		m_entities[i]->update(dt);
	}
	removeDead();
}

void World::draw(Renderer& renderer, const Camera& camera) const 
{
	for (int i = 0;i < m_entities.getSize();i++) 
	{
		m_entities[i]->draw(renderer, camera);
	}
}

int World::getCount() const 
{
	return m_entities.getSize();
}

void World::removeDead() 
{
	for (int i = 0;i < m_entities.getSize();i++)
	{
		if (!m_entities[i]->isAlive()) 
		{
			delete m_entities[i];
			m_entities[i] = m_entities[m_entities.getSize() - 1];
			m_entities.pop_back();//swap-and-pop,since order doesn't matter here
			i--;//now index has changed ,so we need to re-scan "this" index
		}
	}
}