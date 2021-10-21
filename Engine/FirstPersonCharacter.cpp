#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Timer.h"
#include "input.h"
#include "Game.h"

FirstPersonCharacter::FirstPersonCharacter(char* nameP) :
	Actor(nameP)
{}

FirstPersonCharacter::~FirstPersonCharacter() {}

void FirstPersonCharacter::init()
{
	Camera* camera = new Camera(this, "Camera1");
    camera->setPosition(0.0f, 0.0f, 0.0f);

	Actor::init(); // Imperatively after the creation of the component
}

void FirstPersonCharacter::update()
{
    /*
    m_inputState.m_mouse.m_mx = 0;
    entry::processEvents(&m_inputState);

        float*  rotPlayer = getWorldRotation();
        float   rotationPlayer;
        rotationPlayer = rotPlayer[2];
        rotationPlayer += screenCenter - m_inputState.m_mouse.m_mx / 5;

        setWorldRotation(0, 0, rotationPlayer);

        float* playerPos = getWorldPosition();

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

        if (m_inputState.m_key.m_buttons[entry::Key::KeyZ]) {
            setWorldPosition(playerPos[0] + forwardVector[0] * vitesse, playerPos[1] + forwardVector[1] * vitesse, playerPos[2] + forwardVector[2] * vitesse);
        }
        if (m_inputState.m_key.m_buttons[entry::Key::KeyS]) {
            setWorldPosition(playerPos[0] - forwardVector[0] * vitesse, playerPos[1] - forwardVector[1] * vitesse, playerPos[2] - forwardVector[2] * vitesse);
        }
        if (m_inputState.m_key.m_buttons[entry::Key::KeyQ]) {
            setWorldPosition(playerPos[0] + rightVector[0] * vitesse, playerPos[1] + rightVector[1] * vitesse, playerPos[2] + rightVector[2] * vitesse);
        }
        if (m_inputState.m_key.m_buttons[entry::Key::KeyD]) {
            setWorldPosition(playerPos[0] - rightVector[0] * vitesse, playerPos[1] - rightVector[1] * vitesse, playerPos[2] - rightVector[2] * vitesse);
        }
        */
    Component* cam = searchComponent("Camera1");
    if (cam != nullptr) {
        cam->setRotation(0, 0, getWorldRotation()[2]);
    }

	Actor::update(); // Imperatively after the modification
}
