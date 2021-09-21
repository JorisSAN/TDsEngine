#include "Game.h"
#include "Component.h"
#include "Cube.h"
#include <iostream>

bool Game::initialize() {
    return !window.init();
}

void Game::load() {
    // Creation of an Actor
    Actor* actor = new Actor();

    // Creation of a cube
    Cube* cube = new Cube(actor);
    Cube* cube2 = new Cube(actor);

    cube2->setPosition(5, 5, 5);

    actor->setWorldPosition(0, 0, 10);

    // add to all actor of the game
    actors.push_back(actor);

    // Init the Actor
    for (auto a : actors) {
        a->init();
    }

    m_timeOffset = bx::getHPCounter();
}

void Game::loop() {
    while (!window.windowShouldClose()) {
        // update the window (clear, resize, ...)
        window.update();

        /*
        -------------------------------------------------
            Camera View update
        -------------------------------------------------
        */
        const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
        const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
        float view[16];
        bx::mtxLookAt(view, eye, at);
        float proj[16];
        bx::mtxProj(proj, 90.0f, float(window.getWidth()) / float(window.getHeight()), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);
        /*
        -------------------------------------------------
        */

        float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

        // Actor update
        for (auto a : actors) {
            a->setWorldRotation(time * 45, time * 45, time * 45);
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