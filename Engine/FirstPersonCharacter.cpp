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
	camera->setPosition(0.0f, 2.0f, 0.0f);
	camera->setFOV(70);
	Actor::init(); // Imperatively after the creation of the component
}

void FirstPersonCharacter::update()
{
	Component* cam = searchComponent("Camera1");
	if (cam != nullptr) {
		cam->setPosition(getWorldPosition()[0], getWorldPosition()[1], getWorldPosition()[2]);
		cam->setRotation(0, 0, getWorldRotation()[2]);
	}

	Actor::update(); // Imperatively after the modification
}
