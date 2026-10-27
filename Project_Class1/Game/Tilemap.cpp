#include "Tilemap.h"
#include "../Render/Renderer.h"
#include "../Render/Camera.h"

TileType Tilemap::tileAt(int col, int row) const
{
	if (col < 0 || row < 0 || col>= m_col || row >= m_row)
		return TileType::Wall;
	return m_tiles[indexOf(col,row)];
}

void Tilemap::draw(Renderer& renderer,const Camera& camera) const
{
	float camX = camera.getPosition().x;
	float camY = camera.getPosition().y;
	int startX = static_cast<int>(camX / m_tilesize.x) - 1 ;
	int endX = static_cast<int>((camX + camera.getScreenWidth()) / m_tilesize.x) + 1;
	int startY = static_cast<int>(camY / m_tilesize.y) - 1;
	int endY = static_cast<int>((camY+ camera.getScreenHeight()) / m_tilesize.y) + 1;

	if (startX < 0)
		startX = 0;
	if (endX > m_col)
		endX = m_col;
	if (startY < 0)
		startY = 0;
	if (endY > m_row)
		endY = m_row;

	for (int row = startY;row < endY;row++) 
	{
		for (int col = startX;col < endX;col++) 
		{
			Vec2 worldCoord { static_cast<float>(col) * m_tilesize.x ,static_cast<float>(row) * m_tilesize.y };
			Vec2 screenCoord = camera.worldToScreen(worldCoord);
			switch (m_tiles[indexOf(col,row)])
			{
			case TileType::Wall:
				renderer.drawRect( static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y), static_cast<int>(m_tilesize.x), static_cast<int>(m_tilesize.y)
					, 0, 0, 0);
				break;
			case TileType::Road:
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
	float startCol = r.x / m_tilesize.x;
	float endCol = (r.x + r.w) / m_tilesize.x;
	float startRow = r.y / m_tilesize.y;
	float endRow = (r.y + r.h) / m_tilesize.y;
	for (int row = static_cast<int>(startRow);row < endRow;row++)
	{
		for (int col = static_cast<int>(startCol);col < endCol;col++)
		{
			if (isSolid(tileAt(col, row)))
				return true;
		}
	}
	return false;
}