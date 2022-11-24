#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string textureID) : textureID(textureID)
{
	// TODO: add something to load the texture file if it is not already loaded?
	this->setTexture(textureID);
}

// called whenever a component is added to a gameObject in addComponent(TArgs&&... args) 
void SpriteComponent::init()
{
	transform = owner->getComponentByType<TransformComponent>();
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = transform->getTransformWidth(); // set the sprite dimensions equal to the transform
	srcRect.h = transform->getTransformHeight();
}

void SpriteComponent::update(float deltaTime)
{
	dstRect.x = (int)transform->getTransformPosition().x; // keep the rendering target position with the transform of the gameObject
	dstRect.y = (int)transform->getTransformPosition().y;
	dstRect.w = (int)(transform->getTransformWidth() * transform->getTransformScale()); // keep the sprite scaled equal to the transform
	dstRect.h = (int)(transform->getTransformHeight() * transform->getTransformScale());
	//std::cout << "dstRect-x: " << this->dstRect.x << std::endl;
	//std::cout << "dstRect-y: " << this->dstRect.y << std::endl;
	//std::cout << "dstRect-w: " << this->dstRect.w << std::endl;
	//std::cout << "dstRect-h: " << this->dstRect.h << std::endl;
}

void SpriteComponent::render()
{
	// TODO: modify this if we add angle/centerpoint to the sprite component
	LTexture::draw(Game::mainRender, texture, &srcRect, &dstRect, 0.0, NULL, this->flip);
	//std::cout << "we rendered the sprite with textureID: " << this->textureID << std::endl;
}

std::string SpriteComponent::getType() const
{
	return std::string("SpriteComponent");
}

void SpriteComponent::setTexture(std::string textureID)
{
	this->texture = Game::assManager->getTexture(textureID);
}
