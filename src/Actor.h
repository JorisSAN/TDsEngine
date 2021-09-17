#pragma once
#include "Component.h"
#include <vector>

class Actor
{
public:
	Actor(std::vector<Component*> comp);
	~Actor();

	void setWorldPosition(float* pos);
	void setWorldPosition(float x, float y, float z);

	void init();
	void update();
	void destroy();

private:
	std::vector<Component*> components;
	float					m_WorldPosition[3] = { 0, 0, 0 };
};

