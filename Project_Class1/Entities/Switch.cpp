#include "Switch.h"
#include "Entity.h"
#include <cassert>

void Switch::update(float dt)
{
	bool touching{ getBounds().intersects(m_target->getBounds()) };
	if (touching && !m_wasTouching) 
	{
		m_on = !m_on;
		m_texture = m_on ? m_texOn : m_texOff;
		for (int i = 0;i < m_targetCount;i++) 
		{
			Entity* e = m_world->findById(m_targetIds[i]);
			if(e!=nullptr)
			{
				e->onTriggered();
			}
		}
	}
	m_wasTouching = touching;
}

void Switch::addTarget(int id)
{
	assert(m_targetCount < kMaxTargets);
	assert(id >= 0);
	m_targetIds[m_targetCount] = id;
	m_targetCount++;
}

EntityType Switch::getType() const 
{
	return EntityType::Switch;
}

void Switch::save(std::ostream& out) const 
{
	Entity::save(out);
	out << m_on << ' ' << m_wasTouching << ' ' << m_targetCount << ' ';
	for (int i = 0;i < m_targetCount;i++)
	{
		out << m_targetIds[i] << ' ';
	}
}

void Switch::load(std::istream& in) 
{
	Entity::load(in);
	in >> m_on;
	m_texture = m_on ? m_texOn : m_texOff;//reload tex
	in >> m_wasTouching >> m_targetCount;
	assert(m_targetCount <= kMaxTargets);//avoid out of C-style array
	for (int i = 0;i < m_targetCount;i++)
	{
		in >> m_targetIds[i];
	}
}