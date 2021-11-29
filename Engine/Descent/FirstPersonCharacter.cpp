#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Timer.h"
#include "Teleporteur.h"
#include "input.h"
#include "Game.h"
#include <iostream>

FirstPersonCharacter::FirstPersonCharacter(char* nameP) :
	Actor(nameP)
{}

FirstPersonCharacter::~FirstPersonCharacter() {}

void FirstPersonCharacter::init()
{
    Camera* camera = new Camera(this, "Camera1");
    camera->setPosition(0.0f, 0.0f, 0.0f);
    camera->setRotation(0.0f, 0.0f, 0.0f);
	CollisionComponent* colision = new CollisionComponent(this, "CollisionComp", OwnerType::player);
	colision->setScale(1.f, 1.f, 1.f);
	Actor::init(); // Imperatively after the creation of the component
}

void FirstPersonCharacter::update()
{
    float time = Timer::getTime();
    float* playerPos = getWorldPosition();

    float oldPlayerPos[3] = {playerPos[0],playerPos[1] ,playerPos[2] };
    float forwardVector[3];
    forwardVector[0] = getActorForwardVector()[0];
    forwardVector[2] = getActorForwardVector()[1];
    forwardVector[1] = getActorForwardVector()[2];

    float rightVector[3];
    rightVector[0] = getActorRightVector()[0];
    rightVector[1] = getActorRightVector()[1];
    rightVector[2] = getActorRightVector()[2];

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
        cam->setRotation(getWorldRotation()[0], getWorldRotation()[1], getWorldRotation()[2]);
        //cam->update();
    }

    //std::cout << "Cam : x = " << getWorldRotation()[0] << " | y = " << getWorldRotation()[1] << " | z = " << getWorldRotation()[2] << std::endl;

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
                float oldPos[3] = { oldPosition[0],oldPosition[1],oldPosition[2] };
                float newPos[3] = { getWorldPosition()[0],getWorldPosition()[1] ,getWorldPosition()[2] };
                float colMax[3] = { col->getMax()[0] ,col->getMax()[1] ,col->getMax()[2] };
                float colMin[3] = { col->getMin()[0],col->getMin()[1],col->getMin()[2] };
                float myColMax[3] = { myCol->getMax()[0],myCol->getMax()[1],myCol->getMax()[2] };
                float myColMin[3] = { myCol->getMin()[0],myCol->getMin()[1],myCol->getMin()[2] };
                float dx1 = colMax[0] - myColMin[0];
                float dx2 = colMin[0] - myColMax[0];
                float dy1 = colMax[1] - myColMin[1];
                float dy2 = colMin[1] - myColMax[1];
                float dz1 = colMax[2] - myColMin[2];
                float dz2 = colMin[2] - myColMax[2];

                float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;
                float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;
                float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

                if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <= Maths::abs(dz))
                {
                    newPos[0] += dx;
                }
                else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <= Maths::abs(dz))
                {
                    newPos[1] += dy;
                }
                else
                {
                    newPos[2] += dz;
                }

                setWorldPosition(newPos);

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
