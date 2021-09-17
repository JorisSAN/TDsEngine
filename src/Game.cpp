#include "Game.h"
#include "EngineUtils.h"
#include "Component.h"
#include "Cube.h"
#include <iostream>

Game::Game() {
    init();
}

void Game::init() {

    // Creation of a cube
    Cube cube;
    std::vector<Component*> vComponent;
    vComponent.emplace_back(&cube);

    // Creation of an Actor
    Actor actor(vComponent);

    // add to all actor of the game
    allActor.emplace_back(actor);

    // Init the Actor
    for (Actor a : allActor) {
        a.init();
    }
}

void Game::update(int width, int height) {
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
    bx::mtxProj(proj, 90.0f, float(width) / float(height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
    bgfx::setViewTransform(0, view, proj);
    /*
    -------------------------------------------------
    */

    // Actor update
    for (Actor a : allActor) {
        a.update();
    }

    // Go to the next frame
    bgfx::frame();
}

void Game::destroy() {
    // Always in this order
    // Destroy the actor
    for (Actor a : allActor) {
        a.destroy();
    }

    // Shutdown bgfx
    bgfx::shutdown();
}