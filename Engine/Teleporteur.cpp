#include "Teleporteur.h"
#include "Cube.h"
#include "CollisionComponent.h"
#include "Maths.h"
#include "MathMatrix.h"
#include "Timer.h"

Teleporteur::Teleporteur(char* nameP) :
	Actor(nameP)
{}
Teleporteur::Teleporteur(char* nameP,float* position) :
	Actor(nameP)
{
	setTeleporteur(position);
}

Teleporteur::~Teleporteur() {}

void Teleporteur::init()
{
	CollisionComponent* colision = new CollisionComponent(this, "Colision", OwnerType::teleporteur);
	colision->setPosition(0.0f, 0.0f, 0.0f);
	colision->setScale(1.0f, 1.0f, 1.0f);
	Cube* cube = new Cube(this, "Cube");
	cube->setPosition(0.0f, 0.0f, 0.0f);
	cube->setScale(0.5f, 0.5f, 0.5f);
	Actor::init(); // Imperatively after the creation of the component
}

void Teleporteur::update()
{

	Actor::update(); // Imperatively after the modification
}
void Teleporteur::setTeleporteur(float* position) {
	tpPosition[0] = position[0];
	tpPosition[1] = position[1];
	tpPosition[2] = position[2];
}
