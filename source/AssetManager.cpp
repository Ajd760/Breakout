#include "AssetManager.h"
#include "Game.h"

AssetManager::AssetManager(GameObjectManager* manager) : gameObjManager(manager)
{
}

AssetManager::~AssetManager()
{
	destroyEverything();
	gameObjManager = nullptr;
}

void AssetManager::destroyEverything()
{
	//TODO: is this missing anything?
	textures.clear();
}

void AssetManager::addTexture(std::string textureID, std::string path)
{
	SDL_Texture* tex = LTexture::loadTextureFromFile(path, Game::mainRender);
	if (tex != NULL)
	{
		textures.emplace(textureID, tex);
	}
	else
	{
		std::cout << "Error trying to load texture: " << textureID << " from path: " << path << std::endl;
	}
}

SDL_Texture* AssetManager::getTexture(std::string textureID) const
{
	if (this->textures.at(textureID) != nullptr)
		return this->textures.at(textureID);
	else
	{
		std::cerr << textureID << std::endl;
		return nullptr;
	}
}
