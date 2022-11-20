#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "components/Component.h"

class GameObjectManager;

class GameObject
{
public:
	std::string name;

	GameObject(GameObjectManager& manager);
	GameObject(GameObjectManager& manager, std::string name);
	~GameObject();
	void update(float deltaTime);
	void render();
	void destroy();
	bool getIsActive() const;
	int getNumComponents() const;
	Component* getComponentByIndex(int index) const;

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... args) 
	{
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		newComponent.init();
		return *newComponent;
	}

protected:
	GameObjectManager& manager;
	bool bisActive;
	std::vector<Component*> components;
};

