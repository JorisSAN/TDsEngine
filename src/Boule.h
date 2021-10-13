#pragma once
#include "Actor.h"

class Boule : public Actor
{
public:
	Boule(char* nameP);
	virtual ~Boule();
	Boule(const Actor&) = delete;
	Boule& operator=(const Boule&) = delete;
	void init()		override;
	void update()	override;
	void setGoalAndPerson(float* gPos, float* pPos);
	void updateLerp();
private:
	float goalPosition[3] = { 0, 5, 0 };
	bool isLaunched = false;
	float personPosition[3] = { 0, 5, 0 };
	float alphaLerp=0;

};

