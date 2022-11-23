#pragma once
#include "Component.h"
#include "../graphics/LTexture.h"
#include "../GameObject.h"
#include "../Game.h"

class SpriteComponent : public Component
{
public:
	void init() override;
	//void init(); //with params?
	void update(float deltaTime) override;
	void render() override;
	std::string getType() const override;
protected:
	LTexture* texture;
};

