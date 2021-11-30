#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(char* nameP);
	virtual ~Enemy();
	Enemy(const Actor&) = delete;
	Enemy& operator=(const Enemy&) = delete;

	void init()		override;
	void update()	override;


private:
	float lastTimeShot;
	float nextShotCD;
	float damage = 10;
};

