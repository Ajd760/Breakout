#pragma once
#include <map>
#include <string>
#include <SDL.h>

#include "GameObjectManager.h"
#include "graphics/LTexture.h"


// this class is to hold and track loaded assets, i.e. textures/sounds/etc
class AssetManager
{
public:
	AssetManager(GameObjectManager* manager);
	~AssetManager();
	void destroyEverything();
	void addTexture(std::string textureID, std::string path);
	SDL_Texture* getTexture(std::string textureID) const;
private:
	GameObjectManager* gameObjManager;
	//need to revisit std::map but seems best for holding a 2 column structure 
	// of textureIDs mapped to the loaded texture
	std::map<std::string, SDL_Texture*> textures;
};

