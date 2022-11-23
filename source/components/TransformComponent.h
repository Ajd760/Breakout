#pragma once
#include <glm.hpp>
#include <SDL.h>

#include "Component.h"
#include "../Game.h"

class TransformComponent : public Component
{
public:
	TransformComponent(float xPos, float yPos, float xVel, float yVel, unsigned int w, unsigned int h, float s);
	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void render(Uint8 r=255, Uint8 g=255, Uint8 b=255, Uint8 a=255); //render transform rect with rgba value
	std::string getType() const;
	glm::vec2 getTransformPosition() const;
	glm::vec2 getTransformVelocity() const;
	int getTransformWidth() const;
	int getTransformHeight() const;
	float getTransformScale() const;

protected:
	glm::vec2 position;
	glm::vec2 velocity;
	int width;
	int height;
	float scale;
};

