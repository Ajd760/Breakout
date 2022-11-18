#pragma once
#include "GameObject.h"
#include "Component.h"

class GameObjectManager
{
public:
	GameObject& addGameObject(std::string gameObjName);
	std::vector<GameObject*> getGameObjects() const;

	void update(float deltaTime);
	void render();
	bool isEmpty() const;
	unsigned int getGameObjCount() const;
	void destroyEverything();
	void listGameObjects() const;

protected:
	std::vector<GameObject*> gameObjects;
};

