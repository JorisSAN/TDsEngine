#include "Level.h"
#include "Cube.h"
#include "Maths.h"
#include "MathMatrix.h"
#include "Timer.h"

Level::Level(char* nameP) :
	Actor(nameP)
{}

Level::~Level() {}

void Level::init()
{
	Actor::init(); // Imperatively after the creation of the component
}

void Level::update()
{

	Actor::update(); // Imperatively after the modification
}
