#include "Renderer.h"

void Renderer::clear()
{
	m_window.clear();
}
void Renderer::present()
{
	m_window.present();
}

void Renderer::drawRect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	int width = m_window.getWidth();
	int height = m_window.getHeight();
	int startX = std::max(x, 0);
	int endX = std::min(x + w, width);
	int startY = std::max(y, 0);
	int endY = std::min(y + h, height);

	for (int sy = startY;sy < endY;sy++)
	{
		for (int sx = startX;sx < endX;sx++)
		{
			m_window.draw(sx, sy, r, g, b);
		}
	}
}

void Renderer::drawImage(const GamesEngineeringBase::Image& img, int x, int y) 
{
	int width = static_cast<int>(img.width);
	int height = static_cast<int>(img.height);
	int widthW = m_window.getWidth();
	int heightW = m_window.getHeight();
	int startX = std::max(x, 0);
	int endX = std::min(x + width, widthW);
	int startY = std::max(y, 0);
	int endY = std::min(y + height, heightW);
	for (int sy = startY;sy < endY;sy++)
	{
		for (int sx = startX;sx < endX;sx++)
		{
			if(img.alphaAtUnchecked(sx-x,sy-y)>=210)
				m_window.draw(sx, sy,img.atUnchecked(sx-x,sy-y));
		}
	}
}