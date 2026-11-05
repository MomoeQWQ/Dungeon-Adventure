#pragma once
#include "../Core/Vec2.h"

//Camera class, responsible for managing the camera's position and view in the game world, allowing it to follow a target and convert world coordinates to screen coordinates
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
	int getScreenWidth() const;
	int getScreenHeight() const;
	void setClamp(bool);

private:
	Vec2 m_position{};//top-left point of the screen
	int m_worldWidth{};
	int m_worldHeight{};
	int m_screenWidth{};
	int m_screenHeight{};
	bool m_clamp{ true };
};

