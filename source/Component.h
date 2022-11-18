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
	virtual ~Component();
	virtual void init();
	virtual void update(float deltaTime);
	virtual void render();
	virtual std::string getType() const;
};