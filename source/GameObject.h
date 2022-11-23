#pragma once
#include <glm.hpp>
#include <iostream>
#include <string>
#include <vector>

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
	glm::vec2 getTransformPosition() const;

	// create and add a component to the gameObject, and return a reference to the component
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... args) 
	{
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		newComponent->init();
		return *newComponent;
	}

#if true //compiler directive to turn on/off for debugging
	//TODO: test this more thoroughly or rewrite it
	// Component Types:
	//- TransformComponent
	//- SpriteComponent
	template <typename T>
	T* getComponentByType(std::string componentType)
	{
		for (T* component : components)
		{
			if (component->getType() == componentType)
				return component;
		}
		return nullptr;
	}
#endif

protected:
	GameObjectManager& manager;
	bool bisActive;
	std::vector<Component*> components;
};
