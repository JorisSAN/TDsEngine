#pragma once
#include "Actor.h"
#include "common.h"
#include "Window.h"
#include "Timer.h"

class FirstPersonCharacter : public Actor
{
public:
	FirstPersonCharacter(char* nameP);
	virtual ~FirstPersonCharacter();
	FirstPersonCharacter(const Actor&) = delete;
	FirstPersonCharacter& operator=(const FirstPersonCharacter&) = delete;

	void init()		override;
	void update()	override;

	bool canShoot() { return (Timer::getTime()-lastTimeShot)>delayShot; }
	void setLastTimeShot(float time) { lastTimeShot= time; }
	float getVitesse() { return vitesse; }
	void fixCollision(float* oldPosition);

private:

	float vitesse = 0.25f;
	float screenCenter = 0;
	float lastTimeShot = 0; 
	float delayShot = 0.3;
};

