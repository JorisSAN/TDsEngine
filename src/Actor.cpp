#include "Actor.h"

Actor::Actor(std::vector<Component*> comp) {
	components = comp;
}

Actor::~Actor() {
	this->destroy();
}

void Actor::init() {
	for (auto c : components) {
		c->init();
	}
}

void Actor::update() {
	for (auto c : components) {
		c->update();
	}
}

void Actor::destroy() {
	for (auto c : components) {
		c->destroy(); 
	}
	components.clear();
}