#pragma once
#include "Actor.h"
#include "common.h"
#include "Window.h"

class FirstPersonCharacter : public Actor
{
public:
	FirstPersonCharacter(char* nameP);
	virtual ~FirstPersonCharacter();
	FirstPersonCharacter(const Actor&) = delete;
	FirstPersonCharacter& operator=(const FirstPersonCharacter&) = delete;

	void init()		override;
	void update()	override;

private:
	entry::InputState m_inputState;
	float vitesse = 1.0f;
	float screenCenter = 0;
};

