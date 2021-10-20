#include "Boule.h"
#include "Cube.h"
#include "Maths.h"
#include "CollisionComponent.h"
#include "MathMatrix.h"
#include <iostream>
#include <string>
#include "Timer.h"
Boule::Boule(char* nameP) :
	Actor(nameP)
{}

Boule::~Boule() {}

void Boule::init()
{
	CollisionComponent* collision = new CollisionComponent(this, "colcube");
	collision->setScale(1, 1, 1);
	collision->setScale(0, 0, 0);
	Cube* base = new Cube(this, "boulet");
	base->setScale(1, 1, 1);
	base->setPosition(0, 0.0f, 0.0f);
	Actor::init(); // Imperatively after the creation of the component

}

void Boule::setGoalAndPerson(float* gPos, float* pPos,float time)
{
	goalPosition[0] = gPos[0];
	goalPosition[1] = gPos[1];
	goalPosition[2] = gPos[2]; 
	personPosition[0] = pPos[0];
	personPosition[1] = pPos[1];
	personPosition[2] = pPos[2];
	isLaunched = true;
	timeLaunch = time;
	std::cout << " AAAAAAAAAAAAAAAAAAAAAA    " + std::to_string(gPos[0]) + "     " + std::to_string(gPos[0]) + "    " + std::to_string(gPos[0])  << " BBB " + std::to_string(pPos[0]) + "     " + std::to_string(pPos[0]) + "    " + std::to_string(pPos[0]) + "\n";

}
void Boule::updateLerp() {
	alphaLerp = (Timer::getTime() - timeLaunch) < 1 ? Timer::getTime() - timeLaunch : 2-(Timer::getTime() - timeLaunch);
}
void Boule::update()
{
	if (isLaunched) {
		std::cout << "hey ho"+ std::to_string(alphaLerp);
		float xlerp = Maths::lerp(personPosition[0], goalPosition[0], alphaLerp);
		float ylerp = Maths::lerp(personPosition[1], goalPosition[1], alphaLerp);
		float zlerp = Maths::lerp(personPosition[2], goalPosition[2], alphaLerp);
		std::cout << "     " +std::to_string(xlerp)+ "     "+ std::to_string(ylerp)+"    "+ std::to_string(zlerp)+"\n";

		setWorldPosition(xlerp, ylerp, zlerp);
		(float)bx::getHPFrequency();
		if (Timer::getTime()-timeLaunch  > 2) {
			isLaunched = false;
		}
	}
	fixCollision();
	Actor::update(); // Imperatively after the modification
}

void Boule::fixCollision() {
	CollisionComponent* cam = static_cast<CollisionComponent*>(searchComponent("colcube"));

}
