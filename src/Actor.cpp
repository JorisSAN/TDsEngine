#include "Actor.h"
#include "Component.h"
#include "Game.h"

Actor::Actor() :
	game(Game::instance())
{
	game.addActor(this);
}

Actor::~Actor() {
	destroy();
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
	components.clear();
}

void Actor::addComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}