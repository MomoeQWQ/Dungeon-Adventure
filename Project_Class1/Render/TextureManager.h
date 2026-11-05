#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/DynamicArray.h"
#include <string>

//TextureManager class, responsible for loading and managing textures in the game, allowing them to be loaded from files and retrieved by name
class TextureManager
{
public:
	TextureManager() = default;
	~TextureManager();
	TextureManager(const TextureManager& source) = delete;
	TextureManager& operator=(const TextureManager& source)= delete;
	const GamesEngineeringBase::Image* load(const std::string& name, const std::string& path);
	const GamesEngineeringBase::Image* get(const std::string& name) const;

private:
	int findIndex(const std::string& name) const;
	DynamicArray<GamesEngineeringBase::Image*> m_images;
	DynamicArray<std::string> m_names;
};
