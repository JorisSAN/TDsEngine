#include "Enemy.h"
#include "Cube.h"
#include "CollisionComponent.h"
#include "Maths.h"
#include "FirstPersonCharacter.h"
#include "MathMatrix.h"
#include "Balle.h"
#include "Timer.h"
#include "Game.h"
#include <string>


Enemy::Enemy(char* nameP) :
	Actor(nameP)
{
}

Enemy::~Enemy() {}

void Enemy::init()
{
	CollisionComponent* colision = new CollisionComponent(this, "Colision",OwnerType::enemy);
	colision->setPosition(0.0f, 0.0f, 0.0f);
	colision->setScale(1.0f, 2.0f, 1.0f);
	Cube* cube = new Cube(this, "Cube ennemy");
	cube->setPosition(0.0f, 0.0f, 0.0f);
	cube->setScale(1.0f, 2.0f, 1.0f);
	lastTimeShot = 0;
	nextShotCD = static_cast <float> (2 +( rand()) / (static_cast <float> (RAND_MAX / 3)));

	Actor::init(); // Imperatively after the creation of the component
}

void Enemy::update()

{

	if (lastTimeShot + nextShotCD <Timer::getTime()) {
		std::cout << "enemy " << getName() << " has shot at " << Timer::getTime() << "   \n";

		lastTimeShot = Timer::getTime();
		nextShotCD = static_cast <float> (2 + (rand()) / (static_cast <float> (RAND_MAX / 3)));
		FirstPersonCharacter* player = static_cast<FirstPersonCharacter*>(Actor::getGame().searchActor("FirstPersonCharacter"));
		float xa = getActorForwardVector()[0];
		float xb = player->getWorldPosition()[0] - getWorldPosition()[0];
		float ya = getActorForwardVector()[1];
		float yb = player->getWorldPosition()[1] - getWorldPosition()[1] ;
		float za = getActorForwardVector()[2];
		float zb = player->getWorldPosition()[2] -getWorldPosition()[2];

		float rotator[3] = { 0,0,0 };
		rotator[0] = Maths::acos((xa*xb +ya*yb)/(sqrt(xa*xa+ya*ya)*sqrt(xb*xb+yb*yb)));
		rotator[1] = Maths::acos((xa * xb + ya * yb) / (sqrt(xa * xa + ya * ya) * sqrt(xb * xb + yb * yb)));
		rotator[2] = Maths::acos((xa * xb + ya * yb) / (sqrt(xa * xa + ya * ya) * sqrt(xb * xb + yb * yb)));
		
		//lag intensif need instancing//
		Balle* bullet = new Balle(&("bullet " + std::to_string(Timer::getTime()))[0]);
		bullet->init();
		bullet->setRotStartInstigator( rotator, getWorldPosition(), OwnerType::enemy);
	


	}
	Actor::update(); // Imperatively after the modification

	
}
