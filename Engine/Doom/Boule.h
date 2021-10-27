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
	void setGoalAndPerson(float* gPos, float* pPos,float time);
	void setPerson(float* pPos);
	void updateLerp();
	bool getIsLaunched() {return isLaunched;};
	bool fixCollision(float* oldPosition);
private:
	float goalPosition[3] = { 0, 5, 0 };
	bool isLaunched = false;
	float personPosition[3] = { 0, 5, 0 };
	float alphaLerp=0;
	float timeLaunch=0;
	float complementTime = 0;
};

