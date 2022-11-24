#include "TransformComponent.h"


TransformComponent::TransformComponent(float xPos, float yPos, float xVel, float yVel, unsigned int w, unsigned int h, float s) {
	position = glm::vec2(xPos, yPos);
	velocity = glm::vec2(xVel, yVel);
	width = w;
	height = h;
	scale = s;
}


void TransformComponent::init()
{
//	position = glm::vec2(0.0f, 0.0f);
//	velocity = glm::vec2(0.0f, 0.0f);
//	width = 0;
//	height = 0;
//	scale = 0.0f;
}

void TransformComponent::update(float deltaTime)
{
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
}

void TransformComponent::render()
{
	// only rendering for the transform for debugging , maybe TODO: add a flag to enable/disable this
	/*
	SDL_Rect transformRect = {
	(int)position.x, (int)position.y, width, height
	};
	SDL_SetRenderDrawColor(Game::mainRender, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::mainRender, &transformRect);
	*/
}

void TransformComponent::render(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	// TODO: make a flag or some method for calling this render instead of the blank one
	SDL_Rect transformRect = {
		(int)position.x, (int)position.y, width, height
	};
	SDL_SetRenderDrawColor(Game::mainRender, r, g, b, a);
	SDL_RenderFillRect(Game::mainRender, &transformRect);
}

std::string TransformComponent::getType() const
{
	return std::string("TransformComponent");
}

glm::vec2 TransformComponent::getTransformPosition() const
{
	return position;
}

glm::vec2 TransformComponent::getTransformVelocity() const
{
	return velocity;
}

int TransformComponent::getTransformWidth() const
{
	return width;
}

int TransformComponent::getTransformHeight() const
{
	return height;
}

float TransformComponent::getTransformScale() const
{
	return scale;
}
