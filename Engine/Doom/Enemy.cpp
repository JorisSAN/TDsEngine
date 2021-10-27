#include "Enemy.h"
#include "Cube.h"
#include "CollisionComponent.h"
#include "Maths.h"
#include "MathMatrix.h"
#include "Timer.h"

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
	Cube* cube = new Cube(this, "Cube");
	cube->setPosition(0.0f, 0.0f, 0.0f);
	cube->setScale(1.0f, 2.0f, 1.0f);

	Actor::init(); // Imperatively after the creation of the component
}

void Enemy::update()
{

	Actor::update(); // Imperatively after the modification
}
