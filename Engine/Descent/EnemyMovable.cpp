#include "EnemyMovable.h"
#include "Cube.h"
#include "CollisionComponent.h"
#include "Maths.h"
#include "MathMatrix.h"
#include "Timer.h"

EnemyMovable::EnemyMovable(char* nameP) :
	Actor(nameP)
{
}

EnemyMovable::~EnemyMovable() {}

void EnemyMovable::init()
{
	CollisionComponent* colision = new CollisionComponent(this, "Colision",OwnerType::enemy);
	colision->setPosition(0.0f, 0.0f, 0.0f);
	colision->setScale(1.0f, 2.0f, 1.0f);
	Cube* cube = new Cube(this, "Cube");
	cube->setPosition(0.0f, 0.0f, 0.0f);
	cube->setScale(1.0f, 2.0f, 1.0f);

	Actor::init(); // Imperatively after the creation of the component
}

void EnemyMovable::update()
{

	Actor::update(); // Imperatively after the modification
}
