#pragma once
#include <glm.hpp>

#include "Component.h"
#include "../GameObject.h"

class TransformComponent : public Component
{
public:
	void init(float xPos=0.0f, float yPos=0.0f, float xVel = 0.0f, float yVel = 0.0f);
	void init() override;
	void update(float deltaTime) override;
	void render() override;
	std::string getType() const;
	glm::vec2 getTransformPosition() const;
	glm::vec2 getTransformVelocity() const;

protected:
	glm::vec2 position;
	glm::vec2 velocity;
	unsigned int width;
	unsigned int height;
	float scale;
};

