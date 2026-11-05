#pragma once
#include "../GamesEngineeringBase.h"

//Input.h
class Input {
public:
	static constexpr int kKeyCount{ 256 };
	void update(const GamesEngineeringBase::Window& window);
	bool wasPressed(int key) const;
	bool isDown(int key) const;
private:
	bool m_keyThisFrame[kKeyCount]{};
	bool m_keyLastFrame[kKeyCount]{};
};

