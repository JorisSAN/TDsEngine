#include "Actor.h"

Actor::Actor(std::vector<Component*> comp) {
	components = comp;
}

Actor::~Actor() {
	this->destroy();
}

void Actor::setWorldPosition(float* pos) {
	for (int i = 0; i < sizeof(m_WorldPosition) / sizeof(float); i++) {
		m_WorldPosition[i] = pos[i];
	}
}

void Actor::setWorldPosition(float x, float y, float z) {
	m_WorldPosition[0] = x;
	m_WorldPosition[1] = y;
	m_WorldPosition[2] = z;
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