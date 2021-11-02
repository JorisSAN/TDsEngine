#pragma once
#include "Actor.h"
enum class OwnerType;
class Balle : public Actor
{
public:
	Balle(char* nameP);
	virtual ~Balle();
	Balle(const Actor&) = delete;
	Balle& operator=(const Balle&) = delete;
	void init()		override;
	void update()	override;
	void setRotStartInstigator(float* instRotation, float* pPos, OwnerType pInstig);
	void setSpeed(float pSpeed);
	float getSpeed();
	bool fixCollision(float* oldPosition);
private:
	float goalPosition[3] = { 0, 5, 0 };
	float startPosition[3] = { 0, 5, 0 };
	float speed = 1;
	OwnerType instigator;
	float lifetime = 5;
	float lifeStart = 0;
};
