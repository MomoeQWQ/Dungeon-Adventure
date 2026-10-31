#include "Tilemap.h"
#include "../Render/Renderer.h"
#include "../Render/Camera.h"
#include "../Core/DynamicArray.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>  

TileType Tilemap::tileAt(int col, int row) const
{
	if (m_wrap) 
	{
		col = wrapIndex(col, m_col);
		row = wrapIndex(row, m_row);
	}
	if (col < 0 || row < 0 || col>= m_col || row >= m_row)
		return TileType::Wall;
	return m_tiles[indexOf(col,row)];
}

void Tilemap::draw(Renderer& renderer,const Camera& camera) const
{
	float camX = camera.getPosition().x;
	float camY = camera.getPosition().y;
	int startX = toCol(camX ) - 1 ;
	int endX = toCol(camX + camera.getScreenWidth()) + 1;
	int startY = toRow(camY) - 1;
	int endY = toRow(camY+ camera.getScreenHeight()) + 1;

	if (!m_wrap) {
		if (startX < 0)
			startX = 0;
		if (endX > m_col)
			endX = m_col;
		if (startY < 0)
			startY = 0;
		if (endY > m_row)
			endY = m_row;
	}

	for (int row = startY;row < endY;row++) 
	{
		for (int col = startX;col < endX;col++) 
		{
			Vec2 worldCoord { static_cast<float>(col) * m_tilesize.x ,static_cast<float>(row) * m_tilesize.y };
			Vec2 screenCoord = camera.worldToScreen(worldCoord);
			switch (tileAt(col, row))
			{
			case TileType::Wall:
				if (m_tiletex[static_cast<int>(TileType::Wall)] != nullptr)
					renderer.drawImage(*m_tiletex[static_cast<int>(TileType::Wall)], static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y));
				else
				renderer.drawRect( static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y), static_cast<int>(m_tilesize.x), static_cast<int>(m_tilesize.y)
					, 0, 0, 0);
				break;
			case TileType::Road:
				if (m_tiletex[static_cast<int>(TileType::Road)] != nullptr)
					renderer.drawImage(*m_tiletex[static_cast<int>(TileType::Road)], static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y));
				else
				renderer.drawRect( static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y), static_cast<int>(m_tilesize.x), static_cast<int>(m_tilesize.y)
					, 255, 255, 255);
				break;
			}
			
		}
	}
}

bool Tilemap::isSolid(TileType t)
{
	switch (t) 
	{
	case TileType::Wall:
		return true;
	case TileType::Road:
		return false;
	}
	return true;
}

int Tilemap::indexOf(int col, int row) const
{
	return row * m_col + col ;
}

int Tilemap::getPixelWidth() const
{
	return m_col * static_cast<int>(m_tilesize.x);
}

int Tilemap::getPixelHeight() const
{
	return m_row * static_cast<int>(m_tilesize.y);
}

bool Tilemap::isAreaBlocked(const Rect& r) const
{
	//use float ,so if the boundary lies exactly on a grid line, the < operator excludes the next cell.
	float endCol = (r.x + r.w) / m_tilesize.x;
	float endRow = (r.y + r.h) / m_tilesize.y;
	for (int row = toRow(r.y);row < endRow;row++)
	{
		for (int col = toCol(r.x);col < endCol;col++)
		{
			if (isSolid(tileAt(col, row)))
				return true;
		}
	}
	return false;
}

bool Tilemap::loadFromFile(const std::string& path) 
{
	std::ifstream file{ path };
	if (!file.is_open())
	{
		std::cerr << " map does not exist in " << path << std::endl;
		return false;
	}
	int fCol{}, fRow{}, n{};
	if (!(file >> fCol >> fRow) || fCol <= 0 || fRow <= 0) 
	{
		std::cerr << "file Col/Row is bad to read, zero or minus";
		return false;
	}

	DynamicArray<TileType> temp{};
	for (int row = 0;row < fRow;row++) 
	{
		for (int col = 0;col < fCol;col++) 
		{
			if (!(file >> n))
			{
				std::cerr << " file is shorter than expected " << std::endl;
				return false;
			}
			if (!(n >= 0 && n < static_cast<int>(TileType::Count))) 
			{
				std::cerr << " tile in " << row <<"\t"<<col<<"is not a valid tiletype" << std::endl;
				n = static_cast<int>(TileType::Wall);//set it to W(default)
			}
			temp.push_back(static_cast<TileType>(n));
		}
	}
	m_row = fRow;
	m_col = fCol;
	m_tiles = temp;
	return true;
}

void Tilemap::setTileTexture(TileType type, const GamesEngineeringBase::Image* tex) 
{
	assert(static_cast<int>(type) >= 0 && static_cast<int>(type) < static_cast<int>(TileType::Count));
	m_tiletex[static_cast<int>(type)] = tex;
}

void Tilemap::setWrap(bool wrap)
{
	m_wrap = wrap;
}

bool Tilemap::isWrapping() const
{
	return m_wrap;
}

int Tilemap::wrapIndex(int i, int n) 
{
	return ((i % n) + n) % n;
}

int Tilemap::toCol(float x) const 
{
	return static_cast<int>(std::floor(x / m_tilesize.x));
}

int Tilemap::toRow(float y) const 
{
	return static_cast<int>(std::floor(y / m_tilesize.y));
}