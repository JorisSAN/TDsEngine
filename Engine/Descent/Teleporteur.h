#pragma once
#include "Actor.h"

class Teleporteur : public Actor
{
public:
	Teleporteur(char* nameP);
	Teleporteur(char* nameP,float* position);
	virtual ~Teleporteur();
	Teleporteur(const Actor&) = delete;
	Teleporteur& operator=(const Teleporteur&) = delete;
	void setTeleporteur(float* position);
	float* getTeleporteur() {return tpPosition;};

	void init()		override;
	void update()	override;
	float tpPosition[3] = { 0,0,0 };
};

