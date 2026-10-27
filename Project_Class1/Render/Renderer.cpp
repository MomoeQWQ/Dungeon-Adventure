#include "Renderer.h"
#include <cassert>

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
	drawImage(img, x, y, 0, 0, static_cast<int>(img.width), static_cast<int>(img.height));
}

void Renderer::drawImage(const GamesEngineeringBase::Image& img, int x, int y,int srcX,int srcY,int w,int h)
{
	assert(srcX >= 0 && srcY >= 0 && srcX + w <= img.width && srcY + h <= img.height && "bad srcX/Y range");
	int widthW = m_window.getWidth();
	int heightW = m_window.getHeight();
	int startX = std::max(x, 0);
	int endX = std::min(x + w, widthW);
	int startY = std::max(y, 0);
	int endY = std::min(y + h, heightW);
	for (int sy = startY;sy < endY;sy++)
	{
		for (int sx = startX;sx < endX;sx++)
		{
			if (img.alphaAtUnchecked(sx - x + srcX, sy - y + srcY ) >= kAlphaThreshold)
				m_window.draw(sx, sy, img.atUnchecked(sx - x + srcX, sy - y + srcY));
		}
	}
}