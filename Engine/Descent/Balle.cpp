#include "Balle.h"
#include "Mesh.h"
#include "Maths.h"
#include "MathMatrix.h"
#include <iostream>
#include <string>
#include "CollisionFunctions.h"
#include "Timer.h"
#include "Cube.h"
#include "Game.h"

Balle::Balle(char* nameP) :
	Actor(nameP,true)
{}

Balle::~Balle() {}

void Balle::init()
{
	
	CollisionComponent* collision = new CollisionComponent(this, "coliscube", OwnerType::balle);
	collision->setScale(0.5, 0.5, 0.5);
	
	Cube* base = new Cube(this, "balless");
	base->setScale(0.1, 0.1,0.1);
	base->setPosition(0, 0, 0.0f);
	 
	Actor::init(); // Imperatively after the creation of the component
	
}

void Balle::setRotStartInstigator(float* instRotation, float* pPos, OwnerType pInstig)
{
	goalPosition[0] = instRotation[0];
	goalPosition[1] = instRotation[1];
	goalPosition[2] = instRotation[2];
	startPosition[0] = pPos[0];
	startPosition[1] = pPos[1];
	startPosition[2] = pPos[2];
	setWorldRotation(goalPosition);
	setWorldPosition(startPosition);
	instigator = pInstig;
	lifeStart = Timer::getTime();

}
void Balle::setSpeed(float pSpeed)
{
	speed = pSpeed;

}

float Balle::getSpeed()
{
	return speed;
}

void Balle::update()
{
	//setWorldPosition(startPosition);
	
	float oldPos[3] = { getWorldPosition()[0],getWorldPosition()[1],getWorldPosition()[2] };
	
	if (lifetime < Timer::getTime()-lifeStart) {
		getGame().removeActor(this);
		destroy();
		return;
	}
	float* falseballePos = getWorldPosition();
	float ballePos[3] = {falseballePos[0],falseballePos[1] ,falseballePos[2] };
	float oldBallePos[3] = { ballePos[0],ballePos[1] ,ballePos[2] };

	float* forwardTempVector = getActorForwardVector();
	float forwardVector[3];
	forwardVector[0] = forwardTempVector[0];
	forwardVector[1] = forwardTempVector[2];
	forwardVector[2] = forwardTempVector[1];
	setWorldPosition(ballePos[0] + forwardVector[0] * speed, ballePos[1] + forwardVector[1] * speed, ballePos[2] + forwardVector[2] * speed);

	fixCollision(oldBallePos);
	Actor::update(); // Imperatively after the modification
}

bool Balle::fixCollision(float* oldPosition) {
	//std::cout <<"\n Fix collision\n";

	CollisionComponent* myCol = static_cast<CollisionComponent*>(searchComponent("coliscube"));
	float pos[3] = { getWorldPosition()[0],getWorldPosition()[1],getWorldPosition()[2] };
	auto& collisions = Actor::getGame().getAllCollisions();

	for (auto col : collisions) {
		if (myCol == col) {

			//std::cout << "detection avec lui meme\n";
			continue;
		}

		if (Collisions::IsColliding(myCol, col))
		{
			if (col->ownType == OwnerType::level) {
				
				getGame().removeActor(this);
				//destroy();
				return true;
			}
			if (col->ownType == OwnerType::enemy && instigator == OwnerType::player) {
				//Kill the ennemy
				getGame().removeActor(&col->getOwner());
			}
			if (col->ownType == OwnerType::player && instigator == OwnerType::enemy) {
				//Kill the ennemy
				getGame();
			}

		}

	}
	return false;
}