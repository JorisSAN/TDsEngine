#include "Game.h"
#include "Carousel.h"
#include "FirstPersonCharacter.h"
#include "Camera.h"
#include "Timer.h"
#include "Maths.h"

void Game::initWindow(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) {
    window.init(_argc, _argv, _width, _height);
}

void Game::load() {
    // Creation of an Actor
    Actor* carousel = new Carousel("carousel");
    carousel->setWorldPosition(0, 0, 10);

    Actor* firstPersonCharacter = new FirstPersonCharacter("FirstPersonCharacter");

    // Init the Actor
    for (auto a : actors) {
        a->init();
    }
}

bool Game::loop() {

    if (!entry::processEvents(window.getWidth(), window.getHeight(), window.getDebug(), window.getReset(), &m_mouseState))
    {

        Actor* carousel = searchActor("carousel");
        if (carousel != nullptr) {
            carousel->setWorldRotation(0, 0, -Maths::cos(Timer::getTime()) * 22.5 + 22.5);
        }

        Actor* firstPersonCharacter = searchActor("FirstPersonCharacter");

        // Actor update
        for (auto a : actors) {
            a->update();
        }

        // Go to the next frame
        bgfx::frame();

        return true;
    }

    return false;
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