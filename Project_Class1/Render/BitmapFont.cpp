#include "BitmapFont.h"
#include <iostream>
#include <string>

bool BitmapFont::load(const GamesEngineeringBase::Image* image)
{
	if (image == nullptr)
	{
		std::cerr << "bad font image" << std::endl;
		return false;
	}

	if (image->height <= 1) 
	{
		std::cerr << "font image height is too short" << std::endl;
		return false;
	}

	std::string s{ "0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz.!?:;,'{}%/\\<>@-+=()~#&*^||||| |" };

	enum Color
	{
		Magenta,
		Transparent
	};
	Color tempColor{ Magenta };//set original color to Magenta to load 0
	Color lastColor{ Magenta };

	DynamicArray<int> startX{};
	DynamicArray<int> width{};//temporary array, to defend multiple use of load
	int lastStartX{};

	for (unsigned int i = 0;i < image->width;i++) 
	{
		lastColor = tempColor;
		auto p = image->at(i,0);

		if (p[0] == 255 && p[1] == 0 && p[2] == 255)
			tempColor = Magenta;
		else
			tempColor = Transparent;

		if (tempColor == Transparent && lastColor == Magenta) 
		{
			startX.push_back(static_cast<int>(i));
			lastStartX = static_cast<int>(i);
		}

		if (tempColor == Magenta && lastColor == Transparent)
		{
			width.push_back(static_cast<int>(i) - lastStartX);
		}
	}

	//in case end pixel is not Magenta
	if (tempColor == Transparent) 
	{
		width.push_back(static_cast<int>(image->width) - lastStartX);
	}

	if (!(startX.getSize() == s.length() && width.getSize() == s.length()))
	{
		std::cerr << "font image size is not s.length()!" << std::endl;
		return false;
	}

	for (int i = 0;i < 128;i++)
	{
		m_charToGlyph[i] = -1;
	}

	for (int i=0; i < static_cast<int>(s.length()); i++)
	{
		if (s[i] == '|')
			continue;
		m_charToGlyph[static_cast<unsigned char>(s[i])] = i;
	}

	m_fontImg = image;
	m_height = static_cast<int>(image->height) - 1;
	m_startRow = 1;
	m_startX = startX;
	m_width = width;
	return true;
}

void BitmapFont::drawText(Renderer& renderer, const std::string& text, int x, int y) const
{
	
}

int BitmapFont::glyphIndex(char c) const
{
	if (static_cast<unsigned char> (c) >= 128)
		return -1;
	return m_charToGlyph[c];
}