#pragma once
#include "Actor.h"

class FirstPersonCharacter : public Actor
{
public:
	FirstPersonCharacter(char* nameP);
	virtual ~FirstPersonCharacter();
	FirstPersonCharacter(const Actor&) = delete;
	FirstPersonCharacter& operator=(const FirstPersonCharacter&) = delete;

	void init()		override;
	void update()	override;
};

