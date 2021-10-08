#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Timer.h"

FirstPersonCharacter::FirstPersonCharacter(char* nameP) :
	Actor(nameP)
{}

FirstPersonCharacter::~FirstPersonCharacter() {}

void FirstPersonCharacter::init()
{
	Camera* camera = new Camera(this, "Camera1");
	camera->setPosition(-7.0f, 7.0f, 0.0f);
	camera->setRotation(0.0f, -30.0f, 45.0f);

	Actor::init(); // Imperatively after the creation of the component
}

void FirstPersonCharacter::update()
{
	Component* cam = searchComponent("Camera1");

	Actor::update(); // Imperatively after the modification
}
