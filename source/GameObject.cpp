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
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->update(deltaTime);
	}
}

void GameObject::render()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->render();
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
	return components.size();
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
