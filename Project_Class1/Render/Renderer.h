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

private:
	GamesEngineeringBase::Window& m_window;
};