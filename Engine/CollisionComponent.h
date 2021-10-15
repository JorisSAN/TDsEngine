#pragma once
#include "Component.h"

enum CollisionType { point, sphere, aabb };

class CollisionComponent : public Component
{
public:
	CollisionComponent(Actor* ownerP, char* nameP);
	virtual ~CollisionComponent();
	CollisionComponent() = delete;
	CollisionComponent(const CollisionComponent&) = delete;
	CollisionComponent& operator=(const CollisionComponent&) = delete;
	CollisionType colType;
	void init()		override;
	void update()	override;
	void destroy()	override;
	float radius = 0;

};

