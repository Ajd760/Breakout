#include "SpriteComponent.h"

void SpriteComponent::init()
{
}

void SpriteComponent::update(float deltaTime)
{
}

void SpriteComponent::render()
{
	//How to handle setting the x,y position of the texture? Can we do something like this->owner->getTransform().x?
	//glm::vec2 position = this->owner->getComponentByType("TransformComponent")->getTransformPosition();
	//texture->render(position.x, position.y, Game::mainRender);
}

std::string SpriteComponent::getType() const
{
	//std::string componentType = "SpriteComponent";
	return std::string("SpriteComponent");
}
