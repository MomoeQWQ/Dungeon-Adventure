#include "Camera.h"

void Camera::follow(Vec2 target) 
{
	m_position.x = target.x - (m_screenWidth/2);
	m_position.y = target.y - (m_screenHeight / 2);
	float maxX = m_worldWidth - m_screenWidth;
	float maxY = m_worldHeight - m_screenHeight;
	if (m_position.x < 0)
		m_position.x = 0;//if world is less than screen, now we display it on top-left
	if (m_position.x > maxX)
		m_position.x = maxX;
	if (m_position.y < 0)
		m_position.y = 0;
	if (m_position.y > maxY)
		m_position.y = maxY;
}

Vec2 Camera::worldToScreen(Vec2 world) const
{
	return (world - m_position);
}

Vec2 Camera::getPosition() const
{
	return m_position;
}

int Camera::getScreenWidth() const
{
	return m_screenWidth;
}
int Camera::getScreenHeight() const
{
	return m_screenHeight;
}