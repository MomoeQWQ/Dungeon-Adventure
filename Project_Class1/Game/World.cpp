#include "World.h"
#include "../Render/Renderer.h"
#include "../Render/Camera.h"
#include <cassert>
#include <algorithm>

constexpr int MaxtopN = 8;

World::~World()
{
	clear();
}

void World::add(Entity* e) 
{
	assert(e != nullptr && "enetity cannot be nullptr");
	e->setId(m_nextId++);//set entity id
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
			int value = m_entities[i]->getScoreValue();
			if (value > 0)
			{
				m_score += value;
				m_kills++;
			}
			delete m_entities[i];
			m_entities[i] = m_entities[m_entities.getSize() - 1];
			m_entities.pop_back();//swap-and-pop,since order doesn't matter here
			i--;//now index has changed ,so we need to re-scan "this" index
		}
	}
}

bool World::damageArea(const Rect& area, int damage, Team attacker)
{
	bool hitOne{ false };
	for (int i = 0;i < m_entities.getSize();i++) 
	{
		if (m_entities[i]->getTeam() != Team::Neutral && m_entities[i]->getTeam() != attacker && m_entities[i]->getBounds().intersects(area)) 
		{
			m_entities[i]->onHit(damage);
			hitOne = true;
		}
	}
	return hitOne;
}

//design Id to search magic bullet target by index, aiming at avoiding pointer to visit released memories
//cuz now we visit Id(int) instead of pointer
Entity* World::findById(int id) const
{
	for (int i = 0;i < m_entities.getSize();i++) 
	{
		if (m_entities[i]->getId() == id && m_entities[i]->isAlive())
		{
			return m_entities[i];
		}
	}
	return nullptr;
}

//select TopN highestHp target id
int World::selectHighestHp(Vec2 center, float range, Team attacker, int* outIds, int n) const
{
	assert(outIds != nullptr && "World::selectHighestHp outIds = nullpter!");
	assert(n > 0 && n <= MaxtopN && "now World::selectHighestHp only supports 0 <N <= MaxtopN");
	struct Candidate { int id; int hp; };
	Candidate best[MaxtopN]{};
	int count{ 0 };
	float range2 = range * range;
	for (int i = 0;i < m_entities.getSize();i++)
	{
		int hp = m_entities[i]->getHp();
		if (!m_entities[i]->isAlive())
			continue;

		if (hp <= 0)
			continue;

		if (m_entities[i]->getTeam() == Team::Neutral || m_entities[i]->getTeam() == attacker)
			continue;

		Vec2 d = m_entities[i]->getCenter() - center;
		float d2 = d.x * d.x + d.y * d.y;
		if (d2 > range2)
			continue;

		int k{};
		if (count < n)
		{
			best[count] = Candidate{ m_entities[i]->getId() , hp };
			k = count;
			count++;
		}
		else if (hp > best[n - 1].hp)
		{
			best[n - 1] = Candidate{ m_entities[i]->getId() , hp };
			k = n - 1;
		}
		else
			continue;
		while (k > 0 && best[k - 1].hp < best[k].hp)
		{
			std::swap(best[k - 1], best[k]);
			k--;
		}
	}
	for(int i = 0;i< count;i++)
	{
		outIds[i] = best[i].id;
	}
	return count;
}

void World::clear() 
{
	for (int i = 0;i < m_entities.getSize();i++) 
	{
		delete m_entities[i];//Class World is in charge of memory
		m_entities[i] = nullptr;//for safety
	}
	m_entities.clear();
	m_score = 0;
	m_kills = 0;
}

int World::getScore() const 
{
	return m_score;
}

int World::getKills() const 
{
	return m_kills;
}

// S/L methods
void World::addWithId(Entity* e, int id) 
{
	assert(e != nullptr && "enetity cannot be nullptr");
	e->setId(id);
	m_entities.push_back(e);
	m_nextId = std::max(m_nextId, id + 1);//avoid repeating Id after SL
}

Entity* World::getAt(int i) const 
{
	assert(i >= 0 && i < m_entities.getSize());
	return m_entities[i];
}

void World::setStats(int score, int kills) 
{
	m_score = score;
	m_kills = kills;
}