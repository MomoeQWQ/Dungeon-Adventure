#pragma once
#include"../GamesEngineeringBase.h"
#include <algorithm>

class Renderer
{
public:

	explicit Renderer(GamesEngineeringBase::Window& w)
		:m_window{ w }
	{
	}

	void clear();
	void present();
	void drawRect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b);
	void drawImage(const GamesEngineeringBase::Image& img, int x, int y);
	void drawImage(const GamesEngineeringBase::Image& img, int x, int y, int srcX, int srcY, int w, int h);//for sprite frame resource

private:
	GamesEngineeringBase::Window& m_window;
	static constexpr unsigned char kAlphaThreshold{ 210 };
};