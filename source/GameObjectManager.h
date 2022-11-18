#pragma once
#include "GameObject.h"
#include "Component.h"

class GameObjectManager
{
public:
	void update(float deltaTime);
	void render();
	bool isEmpty() const;
	unsigned int getGameObjCount() const;
	void destroyEverything();
	void listGameObjects() const;
	GameObject& addGameObject(std::string gameObjName);
	std::vector<GameObject*> getGameObjects() const;

protected:
	std::vector<GameObject*> gameObjects;
};

