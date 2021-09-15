#pragma once
#include "Component.h"
#include <vector>

class Actor
{
public:
	Actor(std::vector<Component*> comp);
	~Actor();

	void init();
	void update();
	void destroy();

private:
	std::vector<Component*> components;
};

