#include "TextureManager.h"
#include <fstream>
#include <iostream>
int TextureManager::findIndex(const std::string& name) const
{
	for (int i = 0; i < m_names.getSize(); i++)
	{
		if (name == m_names[i])
			return i;//return image index if it exists in the m_names
	}
	return -1;//no match name
}

const GamesEngineeringBase::Image* TextureManager::load(const std::string& name, const std::string& path) 
{
	//check if Image already exists
	int index = findIndex(name);
	if (index != -1)
		return m_images[index];

	//read file from path and load it
	{
		std::ifstream file{ path };
		if (!file.is_open())
		{
			std::cerr << name << " does not exist in " << path << std::endl;
			return nullptr;
		}
	}

	GamesEngineeringBase::Image* newImage = new GamesEngineeringBase::Image();

	if (!newImage->load(path)) 
	{
		delete newImage;
		std::cout << name << " loading failure happens in " << path << std::endl;
		return nullptr;
	}

	m_names.push_back(name);
	m_images.push_back(newImage);
	std::cout << "loaded " << name << std::endl;
	return newImage;
}

const GamesEngineeringBase::Image* TextureManager::get(const std::string& name) const 
{
	int index = findIndex(name);
	if (index != -1)
		return m_images[index];
	else
		return nullptr;
}

TextureManager::~TextureManager() 
{
	for (int i = 0; i < m_names.getSize(); i++)
	{
		delete m_images[i];
	}
}