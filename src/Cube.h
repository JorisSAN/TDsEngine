#pragma once
#include "Component.h"

class Cube : public Component
{
public:
	Cube(Actor* ownerP);
	virtual ~Cube();
	Cube() = delete;
	Cube(const Cube&) = delete;
	Cube& operator=(const Cube&) = delete;

	void init()			override;
	void update()		override;
	void destroy()		override;
};

