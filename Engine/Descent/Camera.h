#pragma once
#include "Component.h"
#include "Window.h"

class Camera : public Component
{
public:
	Camera(Actor* ownerP, char* nameP);
	virtual ~Camera();
	Camera() = delete;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	void init()		override;
	void update()	override;
	void destroy()	override;

	void setFOV		(float fov_p)		{ fov = fov_p;			}
	void setNear	(float near_p)		{ nearPlan = near_p;	}
	void setFar		(float far_p)		{ farPlan = far_p;		}
	void setWidth	(float width_p)		{ width = width_p;		}
	void setHeight	(float height_p)	{ height = height_p;	}

private :
	float fov		= 90.0f;
	float nearPlan	= 0.1f;
	float farPlan	= 100.0f;
	float width		= 1280;
	float height	= 720;
};

