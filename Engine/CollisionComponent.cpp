#include "CollisionComponent.h"
#include "EngineUtils.h"



CollisionComponent::CollisionComponent(Actor* ownerP, char* nameP) :
    Component(ownerP, nameP)
{
}

CollisionComponent::~CollisionComponent() {
    Component::~Component();
    destroy();
}

void CollisionComponent::init() {
 }

void CollisionComponent::update() {
    Component::update();
}

void CollisionComponent::destroy() {
    Component::destroy();
}