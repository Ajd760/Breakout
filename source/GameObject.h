#pragma once
#include <glm.hpp>
#include <iostream>
#include <map>
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
	void listComponents() const;

	// create and add a component to the gameObject, and return a reference to the component
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... args) 
	{
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		componentToTypeMap[&typeid(*newComponent)] = newComponent; //add the component to the type map to track it for a component getter
		newComponent->init();
		return *newComponent;
	}

	//TODO: test this more thoroughly or rewrite it
	// Component Types:
	//- TransformComponent
	//- SpriteComponent
	template <typename T>
	T* getComponentByType()
	{
		// try using the map added to the base class that keeps track of typeids
		// this would be called like gameObject->getComponentByType<TransformComponent>() similar to unity. Ok like identical to unity
		return static_cast<T*>(componentToTypeMap.at(&typeid(T)));

		/* below has not been working, leaving in here in case i come back to it
		for (T* component : components)
		{
			if (component->getType() == componentType)
				return component;
		}
		return nullptr;
		*/
	}

protected:
	GameObjectManager& manager;
	bool bisActive;
	std::vector<Component*> components;
	std::map<const std::type_info*, Component*> componentToTypeMap; //keeps track of each type of component added to the gameObject
};
