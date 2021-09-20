#pragma once
#include <vector>

class Game;
class Component;

class Actor
{
public:
	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	void setWorldPosition(float* pos);
	void setWorldPosition(float x, float y, float z);

	void addComponent(Component* component);
	void removeComponent(Component* component);

	void init();
	void update();
	void destroy();

private:
	Game& game;
	std::vector<Component*> components;
	float					m_WorldPosition[3]	= { 0, 0, 0 };
	float					m_scale[3]			= { 1, 1, 1 };
	float					m_rotation[3]		= { 0, 0, 0 }; // angle in degrees
};

