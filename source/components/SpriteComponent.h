#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "../Game.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::string textureID);
	void init() override;
	void update(float deltaTime) override;
	void render() override;
	std::string getType() const override;
	void setTexture(std::string textureID);

	SDL_RendererFlip flip = SDL_FLIP_NONE; //default to no flip
protected:
	SDL_Texture* texture;
	std::string textureID;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	TransformComponent* transform; // keep track of the transform of the gameObject this is attached to
	
};

