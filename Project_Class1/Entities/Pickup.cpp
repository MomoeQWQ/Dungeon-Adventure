#include "Pickup.h"

void Pickup::update(float dt) 
{
	if (!getBounds().intersects(m_target->getBounds())) 
	{ 
		return; 
	}
	switch(m_type){
	case PickupType::Health:
	{
		m_target->heal(m_amount);
		break;
	}
	case PickupType::Mana:
	{
		m_target->addMana(m_amount);
		break;
	}
	case PickupType::Key: 
	{
		m_target->addKey();
		break;
	}
	}
	destroy();
}

EntityType Pickup::getType() const 
{
	return EntityType::Pickup;
}