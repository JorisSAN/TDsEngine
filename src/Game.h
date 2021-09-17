#pragma once
#include "Window.h"
#include <vector>
#include "Actor.h"

class Game
{
public:
	Game();

	void init();
	void update(int width, int height);
	void destroy();

private:
	std::vector<Actor> allActor;
};

