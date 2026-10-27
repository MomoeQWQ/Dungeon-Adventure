#pragma once
#include "../Core/DynamicArray.h"
#include "../Core/Vec2.h"
#include "../Core/Rect.h"

class Renderer;
class Camera;
enum class TileType 
{
	Wall = 0,
	Road = 1
};

class Tilemap
{
public:
	Tilemap(int col, int row, Vec2 tileSize)
		:m_col{ col }
		, m_row{row}
		, m_tilesize{tileSize}
	{
		//default test map
		for (int i = 0;i < m_col * m_row;i++) 
		{
			m_tiles.push_back(TileType::Road);
		}
		for (int i = 0;i < m_col * m_row;i++)
		{
			if (i % 50 == 0) 
			{
				m_tiles[i] = TileType::Wall;
			}
		}
	}

	TileType tileAt(int col, int row) const;
	void draw(Renderer&, const Camera&) const;
	static bool isSolid(TileType);
	int getPixelWidth() const;
	int getPixelHeight() const;
	bool isAreaBlocked(const Rect& r) const;

private:
	int m_col{64};
	int m_row{48};
	Vec2 m_tilesize{32.0f,32.0f};

	DynamicArray<TileType> m_tiles{};
	int indexOf(int col, int row) const;
};