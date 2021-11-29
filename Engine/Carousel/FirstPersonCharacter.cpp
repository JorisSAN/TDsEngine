#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Cube.h"
#include "Timer.h"
#include "input.h"
#include "Game.h"

FirstPersonCharacter::FirstPersonCharacter(char* nameP) :
	Actor(nameP)
{}

FirstPersonCharacter::~FirstPersonCharacter() {}

void FirstPersonCharacter::init()
{
    Cube* base1 = new Cube(this, "cube");
    base1->setPosition(3.0f, 0.0f, 0.0f);

	Camera* camera = new Camera(this, "Camera1");
    camera->setPosition(0.0f, 0.0f, 0.0f);

	Actor::init(); // Imperatively after the creation of the component
}

void FirstPersonCharacter::update()
{

    float* playerPos = getWorldPosition(); 
    float time = Timer::getTime();

    float oldPlayerPos[3] = {playerPos[0],playerPos[1] ,playerPos[2] };
    float* forwardTempVector = getActorForwardVector();
    float forwardVector[3];
    forwardVector[0] = forwardTempVector[0];
    forwardVector[1] = forwardTempVector[1];
    forwardVector[2] = forwardTempVector[2];

    float* rightTempVector = getActorRightVector();
    float rightVector[3];
    rightVector[0] = rightTempVector[0];
    rightVector[1] = rightTempVector[1];
    rightVector[2] = rightTempVector[2];

    if (Actor::getGame().m_inputState.m_key.m_buttons[entry::Key::KeyZ]) {
        setWorldPosition(playerPos[0] + forwardVector[0] * 0.25, playerPos[1] + forwardVector[1] * 0.25, playerPos[2] + forwardVector[2] * 0.25);
    }
    if (Actor::getGame().m_inputState.m_key.m_buttons[entry::Key::KeyS]) {
        setWorldPosition(playerPos[0] - forwardVector[0] * 0.25, playerPos[1] - forwardVector[1] * 0.25, playerPos[2] - forwardVector[2] * 0.25);
    }
    if (Actor::getGame().m_inputState.m_key.m_buttons[entry::Key::KeyQ]) {
        setWorldPosition(playerPos[0] + rightVector[0] * 0.25, playerPos[1] + rightVector[1] * 0.25, playerPos[2] + rightVector[2] * 0.25);
    }
    if (Actor::getGame().m_inputState.m_key.m_buttons[entry::Key::KeyD]) {
        setWorldPosition(playerPos[0] - rightVector[0] * 0.25, playerPos[1] - rightVector[1] * 0.25, playerPos[2] - rightVector[2] * 0.25);
    }

    Component* cam = searchComponent("Camera1");
    if (cam != nullptr) {
        cam->setRotation(0, 0, getWorldRotation()[2]);
    }

    Component* cube = searchComponent("cube");
    if (cube != nullptr) {
        cube->setRotation(time * 45, time * 45, 0);
    }

	Actor::update(); // Imperatively after the modification
}