#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Timer.h"
#include "Teleporteur.h"
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
	CollisionComponent* colision = new CollisionComponent(this, "CollisionComp", OwnerType::player);
	colision->setScale(1.f, 1.f, 1.f);
	Actor::init(); // Imperatively after the creation of the component
}

void FirstPersonCharacter::update()
{

    float* playerPos = getWorldPosition();

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
    fixCollision(oldPlayerPos);
    Component* cam = searchComponent("Camera1");
    if (cam != nullptr) {
        cam->setRotation(0, 0, getWorldRotation()[2]);
    }

	Actor::update(); // Imperatively after the modification
}

void FirstPersonCharacter::fixCollision(float* oldPosition) {
	CollisionComponent* myCol = static_cast<CollisionComponent*>(searchComponent("CollisionComp"));
	//float pos[3] = { getWorldPosition()[0],getWorldPosition()[1],getWorldPosition()[2] };
	auto& collisions = Actor::getGame().getAllCollisions();

	for (auto col : collisions) {
		if (myCol == col) {

			//std::cout << "detection avec lui meme\n";
			continue;
		}

		if (Collisions::IsColliding(myCol, col))
		{
			if (col->ownType == OwnerType::level) {
                setWorldPosition(oldPosition);

			}
			if (col->ownType == OwnerType::enemy) {
				//Kill the ennemy
				//destroy();
			}
            if (col->ownType == OwnerType::teleporteur) {
                static_cast<Teleporteur*>(&col->getOwner());
                setWorldPosition(static_cast<Teleporteur*>(&col->getOwner())->getTeleporteur());
            }

		}

	}
}
