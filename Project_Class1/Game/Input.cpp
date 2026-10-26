#include "../GamesEngineeringBase.h"
#include "Input.h"
#include <cassert>

using Window = GamesEngineeringBase::Window;

void Input::update(const Window& window)
{
	for (int i = 0; i < kKeyCount; i++)
	{
		m_keyLastFrame[i] = m_keyThisFrame[i];
	}

	for (int i = 0; i < kKeyCount; i++)
	{
		m_keyThisFrame[i] = (window.keyPressed(i));
	}
}

bool Input::isDown(int key) const
{
	assert(key >= 0 && key < kKeyCount && "input index out of kKeyCount");
	return m_keyThisFrame[key];
}

bool Input::wasPressed(int key) const
{
	assert(key >= 0 && key < kKeyCount && "input index out of kKeyCount");
	return (!m_keyLastFrame[key] && m_keyThisFrame[key]);
}