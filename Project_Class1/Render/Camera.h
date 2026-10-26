#pragma once
#include "../Core/Vec2.h"

class Camera
{
public:
	Camera(int worldWidth, int worldHeight,int screenWidth,int screenHeight)
		: m_worldWidth{ worldWidth }
		, m_worldHeight{ worldHeight }
		, m_screenWidth{ screenWidth }
		, m_screenHeight{ screenHeight }
	{}
	
	void follow(Vec2 target);
	Vec2 worldToScreen(Vec2 world) const;
	Vec2 getPosition() const;

private:
	Vec2 m_position{};//top-left point of the screen
	int m_worldWidth{};
	int m_worldHeight{};
	int m_screenWidth{};
	int m_screenHeight{};
};

