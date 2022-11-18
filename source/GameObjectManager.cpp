#include "GameObjectManager.h"

void GameObjectManager::update(float deltaTime)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update(deltaTime);
	}
}

void GameObjectManager::render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}
}

bool GameObjectManager::isEmpty() const
{
	return gameObjects.empty();
}

unsigned int GameObjectManager::getGameObjCount() const
{
	return gameObjects.size();
}

void GameObjectManager::destroyEverything()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->destroy();
	}
}

void GameObjectManager::listGameObjects() const
{
	if (isEmpty())
	{
		std::cout << "GameObjectManager is empty" << std::endl;
		return;
	}
	for (int i = 0; i < gameObjects.size(); i++)
	{
		std::cout << gameObjects[i]->name << std::endl;
	}
}

GameObject& GameObjectManager::addGameObject(std::string gameObjName)
{
	GameObject *newGameObj = new GameObject(*this, gameObjName);
	gameObjects.emplace_back(newGameObj);
	return *newGameObj;
}

std::vector<GameObject*> GameObjectManager::getGameObjects() const
{
	return gameObjects;
}
