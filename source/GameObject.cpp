#include "GameObject.h"

GameObject::GameObject(GameObjectManager& manager) : manager(manager)
{
	bisActive = true;
}

GameObject::GameObject(GameObjectManager& manager, std::string name) : manager(manager), name(name)
{
	bisActive = true;
}

GameObject::~GameObject()
{
}

void GameObject::update(float deltaTime)
{
	if (bisActive)
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->update(deltaTime);
		}
	}
}

void GameObject::render()
{
	if (bisActive)
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->render();
		}
	}
}

void GameObject::destroy()
{
	bisActive = false;
	// Cleanup/free components
}

bool GameObject::getIsActive() const
{
	return bisActive;
}

int GameObject::getNumComponents() const
{
	return (int)components.size();
}

Component* GameObject::getComponentByIndex(int index) const
{
	if (index < 0 || index > components.size() - 1)
	{
		std::cerr << "Component index out of bounds" << std::endl;
		return nullptr;
	}
	return components[index];
}

glm::vec2 GameObject::getTransformPosition() const
{
	//glm::vec2 position;
	for (auto& component : components)
	{
		if (component->getType() == "TransformComponent")
			//position = component->getTransformPosition();
			break; //TODO fix
	}
	//glm::vec2 position = getComponentByType("TransformComponent")->getTransformPosition();
	return glm::vec2();
}

void GameObject::listComponents() const
{
	for (int i = 0; i < components.size(); i++)
	{
		std::cout << "\t" << components[i]->getType() << std::endl;
	}
}
