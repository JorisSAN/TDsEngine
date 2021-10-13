#include "Game.h"
#include "Carousel.h"
#include "Boule.h"
#include "Level.h"
#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Timer.h"
#include "Maths.h"
#include "LevelLoader.h"
bool Game::initialize() {
    return !window.init();
}

void Game::load() {
    // Creation of an Actor
    Actor* level = new Level("level");
    level->setWorldPosition(0, 0, 10);
    ReadFile(3, level);
    Actor* firstPersonCharacter = new FirstPersonCharacter("FirstPersonCharacter");
    Actor* boule = new Boule("boule");

    // Init the Actor
    for (auto a : actors) {
        a->init();
    }
}

void Game::loop() {
    while (!window.windowShouldClose()) {
        // update the window (clear, resize, ...)
        window.update();
        /*
        Actor* carousel = searchActor("carousel");
        if (carousel != nullptr) {
            carousel->setWorldRotation(0, 0, -Maths::cos(Timer::getTime()) * 22.5 + 22.5);
        }
        */
        Boule* boule = static_cast<Boule*>(searchActor("boule"));
        Actor* firstPersonCharacter = searchActor("FirstPersonCharacter");
        float gPosition[3] = { 5,5,5 };
        //float personPosition[3] = { 0,0,0 };
        float* goalPosition = firstPersonCharacter->getActorForwardVector();
        float* personPosition = firstPersonCharacter->getWorldPosition();
        float* bouleRotation = firstPersonCharacter->getWorldRotation();
        gPosition[0] = goalPosition[0];
        gPosition[1] = goalPosition[1];
        gPosition[2] = goalPosition[2];
        boule->setGoalAndPerson(personPosition,gPosition);
        boule->updateLerp();

        // Actor update
        for (auto a : actors) {
            a->update();
        }

        // Go to the next frame
        bgfx::frame();
    }
}

void Game::unload() {
    actors.clear();
}

void Game::close() {
    bgfx::shutdown();
    window.shutdown();
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