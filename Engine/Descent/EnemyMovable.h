#pragma once
#include "Actor.h"

class EnemyMovable : public Actor
{
public:
	EnemyMovable(char* nameP);
	virtual ~EnemyMovable();
	EnemyMovable(const Actor&) = delete;
	EnemyMovable& operator=(const EnemyMovable&) = delete;

	void init()		override;
	void update()	override;
};

