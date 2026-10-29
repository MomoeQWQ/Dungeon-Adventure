#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/DynamicArray.h"
#include "Renderer.h"
#include <string>

class BitmapFont
{
public:
	BitmapFont() = default;
	bool load(const GamesEngineeringBase::Image* image);
	void drawText(Renderer& renderer, const std::string& text, int x, int y) const;
	int measureText(const std::string& text) const;

private:
	const GamesEngineeringBase::Image* m_fontImg{};
	DynamicArray<int> m_startX{};
	DynamicArray<int> m_width{};
	int m_charToGlyph[128]{};//find table
	int m_height{};
	int m_startRow{};
	int m_letterSpacing{2};

	int glyphIndex(char c) const;//char to glyphIndex, private as we don't use it outside class
};
