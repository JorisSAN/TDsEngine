#pragma once
#include "Component.h"

enum class CollisionType { point, sphere, aabb };
enum class OwnerType { level, enemy,boule,teleporteur,player };
class CollisionComponent : public Component
{
public:
	CollisionComponent(Actor* ownerP, char* nameP);
	CollisionComponent(Actor* ownerP, char* nameP,OwnerType ownerT);
	virtual ~CollisionComponent();
	CollisionComponent() = delete;
	CollisionComponent(const CollisionComponent&) = delete;
	CollisionComponent& operator=(const CollisionComponent&) = delete;
	CollisionType colType;
	void init()		override;
	void update()	override;
	void destroy()	override;
	OwnerType ownType;
	
	float radius = 0;
	float* getMax();
	float* getMin();
};

