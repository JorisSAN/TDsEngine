#pragma once
#include "Actor.h"

class Level : public Actor
{
public:
	Level(char* nameP);
	virtual ~Level();
	Level(const Actor&) = delete;
	Level& operator=(const Level&) = delete;

	void init()		override;
	void update()	override;
};

