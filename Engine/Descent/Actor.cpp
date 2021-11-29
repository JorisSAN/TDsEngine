#include "Actor.h"
#include "Component.h"
#include "Game.h"

Actor::Actor(char* nameP) :
	game(Game::instance())
{
	game.addActor(this);
	setName(nameP);
}

Actor::~Actor() {
	destroy();
}

void Actor::setName(char* nameP)
{
	for (int i = 0; i < sizeof(name) / sizeof(char); i++) {
		name[i] = nameP[i];
		if (nameP[i] == '\0') {
			break;
		}
	}
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

void Actor::setWorldRotation(float* rot) {
	for (int i = 0; i < sizeof(m_WorldRotation) / sizeof(float); i++) {
		m_WorldRotation[i] = rot[i];
	}
}

void Actor::setWorldRotation(float x, float y, float z) {
	m_WorldRotation[0] = x;
	m_WorldRotation[1] = y;
	m_WorldRotation[2] = z;
}

void Actor::setWorldScale(float* scl) {
	for (int i = 0; i < sizeof(m_WorldScale) / sizeof(float); i++) {
		m_WorldScale[i] = scl[i];
	}
}

void Actor::setWorldScale(float x, float y, float z) {
	m_WorldScale[0] = x;
	m_WorldScale[1] = y;
	m_WorldScale[2] = z;
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

Component* Actor::searchComponent(char* componentName)
{
	for (auto c : components) {
		if (c->isTheComponent(componentName)) { 
			return c;
		}
	}
	return nullptr;
}

bool Actor::isTheActor(char* nameP)
{
	for (int i = 0; i < sizeof(name) / sizeof(char); ++i) {
		if (name[i] != nameP[i]) { return false; }
		if (name[i] == '\0' && nameP[i] != '\0') { return false; }
		if (name[i] != '\0' && nameP[i] == '\0') { return false; }
		if (name[i] == '\0' && nameP[i] == '\0') { break; }
	}
	return true;
}

float* Actor::getActorForwardVector() {
	float vector[3];
	float* rotation = getWorldRotation();

	float angleX = Maths::toRadians(rotation[2]);
	float angleY = Maths::toRadians(rotation[1]);

	vector[0] = Maths::cos(angleY) * Maths::cos(angleX);
	vector[1] = Maths::sin(angleY) * Maths::cos(angleX);
	vector[2] = Maths::sin(angleX);

	return vector;
}

float* Actor::getActorRightVector() {
	// Get Forward vector
	float forward[3];
	forward[0] = getActorForwardVector()[0];
	forward[2] = getActorForwardVector()[1];
	forward[1] = getActorForwardVector()[2];

	// Normalize the Forward vector
	float normalizedForward[3];
	normalizedForward[0] = Maths::normalize(forward)[0];
	normalizedForward[1] = Maths::normalize(forward)[1];
	normalizedForward[2] = Maths::normalize(forward)[2];

	// Get and Normalize the Up vector
	const float up[3] = { 0.0f, 1.0f, 0.0f };
	float normalizedUp[3];
	normalizedUp[0] = Maths::normalize(up)[0];
	normalizedUp[1] = Maths::normalize(up)[1];
	normalizedUp[2] = Maths::normalize(up)[2];

	// Calculate the Right Vector
	float right[3];
	right[0] = Maths::cross(normalizedForward, up)[0];
	right[1] = Maths::cross(normalizedForward, up)[1];
	right[2] = Maths::cross(normalizedForward, up)[2];

	return right;
}