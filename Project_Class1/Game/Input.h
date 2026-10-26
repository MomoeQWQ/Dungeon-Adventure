#pragma once
#include "../GamesEngineeringBase.h"

class Input {
public:
	void update(const GamesEngineeringBase::Window& window);
	bool wasPressed(int key) const;
	bool isDown(int key) const;
private:
	static constexpr int kKeyCount{ 256 };
	bool m_keyThisFrame[kKeyCount]{};
	bool m_keyLastFrame[kKeyCount]{};
};

