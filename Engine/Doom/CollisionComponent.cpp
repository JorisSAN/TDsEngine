#include "CollisionComponent.h"
#include "EngineUtils.h"
#include "Game.h"
#include <iostream>



CollisionComponent::CollisionComponent(Actor* ownerP, char* nameP) :
    Component(ownerP, nameP),colType(CollisionType::aabb),ownType(OwnerType::level)
{
    ownerP->getGame().addCollision(this);
}
CollisionComponent::CollisionComponent(Actor* ownerP, char* nameP,OwnerType ownerT) :
    Component(ownerP, nameP), colType(CollisionType::aabb),ownType(ownerT)
{
    ownerP->getGame().addCollision(this);
}
CollisionComponent::~CollisionComponent() {
    Component::~Component();
    destroy();
}

void CollisionComponent::init() {

    Component::init();
}

void CollisionComponent::update() {
    //Component::update();
}

void CollisionComponent::destroy() {
    Component::destroy();
}

float* CollisionComponent::getMax() {
    float vectorMax[3] = { 0,0,0 };
    vectorMax[0] = getWorldPosition()[0] - getScale()[0] > getWorldPosition()[0] + getScale()[0] ?
        getWorldPosition()[0] - getScale()[0] : getWorldPosition()[0] + getScale()[0];
    vectorMax[1] = getWorldPosition()[1] - getScale()[1] > getWorldPosition()[1] + getScale()[1] ?
        getWorldPosition()[1] - getScale()[1] : getWorldPosition()[1] + getScale()[1];
    vectorMax[2] = getWorldPosition()[2] - getScale()[2] > getWorldPosition()[2] + getScale()[2] ?
        getWorldPosition()[2] - getScale()[2] : getWorldPosition()[2] + getScale()[2];
    return vectorMax;
}
float* CollisionComponent::getMin() {
    float vectorMin[3] = { 0,0,0 };
    vectorMin[0] = getWorldPosition()[0] - getScale()[0] < getWorldPosition()[0] + getScale()[0] ?
        getWorldPosition()[0] - getScale()[0] : getWorldPosition()[0] + getScale()[0];
    vectorMin[1] = getWorldPosition()[1] - getScale()[1] < getWorldPosition()[1] + getScale()[1] ?
        getWorldPosition()[1] - getScale()[1] : getWorldPosition()[1] + getScale()[1];
    vectorMin[2] = getWorldPosition()[2] - getScale()[2] < getWorldPosition()[2] + getScale()[2] ?
        getWorldPosition()[2] - getScale()[2] : getWorldPosition()[2] + getScale()[2];
    return vectorMin;
    
}
