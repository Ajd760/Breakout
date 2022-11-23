#pragma once
#include <string>

class GameObject;

/*
* This is fully an abstract class - all methods are 
* implemented by the classes that inherit it
*/
class Component 
{
public:
	GameObject* owner;

	virtual ~Component() = default;
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual std::string getType() const = 0;
};