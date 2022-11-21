#include "TransformComponent.h"

void TransformComponent::init(float xPos, float yPos, float xVel, float yVel)
{
	// these all default to 0.0f
	position.x = xPos;
	position.y = yPos;
	velocity.x = xVel;
	velocity.y = yVel;
}

void TransformComponent::init()
{
	position.x = 0.0f;
	position.y = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
}

void TransformComponent::update(float deltaTime)
{
	position += velocity * deltaTime;
}

void TransformComponent::render()
{
}

std::string TransformComponent::getType() const
{
	return std::string();
}

glm::vec2 TransformComponent::getTransformPosition() const
{
	return position;
}

glm::vec2 TransformComponent::getTransformVelocity() const
{
	return velocity;
}
