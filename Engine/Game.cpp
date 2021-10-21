#include "Game.h"
#include "Carousel.h"
#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Timer.h"
#include "Level.h"
#include "Boule.h"
#include "Enemy.h"
#include "Maths.h"
#include <iostream>
#include "LevelLoader.h"
#include "input.h"

void Game::initWindow(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) {
    window.init(_argc, _argv, _width, _height);
}

void Game::load() {
    file.open("log.txt", std::ios_base::out);
    pipe.redirect(&file);
    // Creation of an Actor
   // Actor* carousel = new Carousel("carousel");
    //carousel->setWorldPosition(0, 0, 10);
    Actor* boule = new Boule("boule");
    Actor* firstPersonCharacter = new FirstPersonCharacter("FirstPersonCharacter");

    Actor* level = new Level("level");
    ReadFile(3, level,firstPersonCharacter);
    // Init the Actor
    for (auto a : actors) {
        a->init();
    }
    //firstPersonCharacter->setWorldPosition(3.0f, 5.0f, 3.0f);


}

bool Game::loop() {
    window.update();

    file.open("log.txt", std::ios_base::out);
    pipe.redirect(&file);
    inputSetMouseLock(false);
    m_inputState.m_mouse.m_mx = 0;
    if (!entry::processEvents(&m_inputState))
    {
        Actor* player = searchActor("FirstPersonCharacter");
        Boule* boule = static_cast<Boule*>(searchActor("boule"));

        if (player != nullptr) {
            float* personPosition = player->getWorldPosition();
            float pPosition[3] = { -7.0f,6.0f,0.0f };
            pPosition[0] = personPosition[0];
            pPosition[1] = personPosition[1];
            pPosition[2] = personPosition[2];
            if (m_inputState.m_mouse.m_buttons[entry::MouseButton::Left] && !boule->getIsLaunched()) {
                
                std::cout << " fromage rape";
                float gPosition[3] = { -0.0f, 6.0f, 0.0f };
                float* goalPosition = player->getActorForwardVector();
                gPosition[0] = goalPosition[0] * 10 + personPosition[0];
                gPosition[1] = goalPosition[1] * 10 + personPosition[1];
                gPosition[2] = goalPosition[2] * 10 + personPosition[2];
               
                boule->setGoalAndPerson(gPosition, pPosition, Timer::getTime());
            }
            boule->setPerson(pPosition);
            float* rotPlayer = player->getWorldRotation();
            float   rotationPlayer;
            rotationPlayer = rotPlayer[2];
            rotationPlayer += 0 - m_inputState.m_mouse.m_mx / 5;

            player->setWorldRotation(0, 0, rotationPlayer);

            float* playerPos = player->getWorldPosition();

            float* forwardTempVector = player->getActorForwardVector();
            float forwardVector[3];
            forwardVector[0] = forwardTempVector[0];
            forwardVector[1] = forwardTempVector[1];
            forwardVector[2] = forwardTempVector[2];

            float* rightTempVector = player->getActorRightVector();
            float rightVector[3];
            rightVector[0] = rightTempVector[0];
            rightVector[1] = rightTempVector[1];
            rightVector[2] = rightTempVector[2];

            if (m_inputState.m_key.m_buttons[entry::Key::KeyZ]) {
                player->setWorldPosition(playerPos[0] + forwardVector[0] * 0.25, playerPos[1] + forwardVector[1] * 0.25, playerPos[2] + forwardVector[2] * 0.25);
            }
            if (m_inputState.m_key.m_buttons[entry::Key::KeyS]) {
                player->setWorldPosition(playerPos[0] - forwardVector[0] * 0.25, playerPos[1] - forwardVector[1] * 0.25, playerPos[2] - forwardVector[2] * 0.25);
            }
            if (m_inputState.m_key.m_buttons[entry::Key::KeyQ]) {
                player->setWorldPosition(playerPos[0] + rightVector[0] * 0.25, playerPos[1] + rightVector[1] * 0.25, playerPos[2] + rightVector[2] * 0.25);
            }
            if (m_inputState.m_key.m_buttons[entry::Key::KeyD]) {
                player->setWorldPosition(playerPos[0] - rightVector[0] * 0.25, playerPos[1] - rightVector[1] * 0.25, playerPos[2] - rightVector[2] * 0.25);
            }
            //boule->setWorldRotation(rotationPlayer[0], rotationPlayer[2], rotationPlayer[1]);

        }

        boule->updateLerp();
    }
    inputSetMouseLock(true);

    /*
    Actor* carousel = searchActor("carousel");
    if (carousel != nullptr) {
        carousel->setWorldRotation(0, 0, -Maths::cos(Timer::getTime()) * 22.5 + 22.5);
    }
    */
    // Actor update
    for (auto a : actors) {
        a->update();
    }

    // Go to the next frame
    bgfx::frame();
    std::cout << "1";

    return true;
}

void Game::unload() {
    actors.clear();
}

void Game::close() {
    bgfx::shutdown();
}

void Game::addActor(Actor* actor)
{
    actors.emplace_back(actor);
}

void Game::removeActor(Actor* actor)
{
    // Erase actor from the two vectors
    auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
    if (iter != end(pendingActors))
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, end(pendingActors) - 1);
        pendingActors.pop_back();
    }
    iter = std::find(begin(actors), end(actors), actor);
    if (iter != end(actors))
    {
        std::iter_swap(iter, end(actors) - 1);
        actors.pop_back();
    }
}

Actor* Game::searchActor(char* actorName)
{
    for (auto a : actors) {
        if (a->isTheActor(actorName)) {
            return a;
        }
    }
    return nullptr;
}


void Game::addCollision(CollisionComponent* collision)
{
    collisions.emplace_back(collision);
}

void Game::removeCollision(CollisionComponent* collision)
{
    // Erase actor from the two vectors
    auto iter = std::find(begin(pendingCollisions), end(pendingCollisions), collision);
    if (iter != end(pendingCollisions))
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, end(pendingCollisions) - 1);
        pendingCollisions.pop_back();
    }
    iter = std::find(begin(collisions), end(collisions), collision);
    if (iter != end(collisions))
    {
        std::iter_swap(iter, end(collisions) - 1);
        collisions.pop_back();
    }
}

std::vector<CollisionComponent*> Game::getAllCollisions() {
    return collisions;
}
