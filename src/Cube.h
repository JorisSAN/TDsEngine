#pragma once
#include "bgfx/bgfx.h"
#include "Component.h"

class Cube : public Component
{
public:
	void init()			override;
	void update()		override;
	void destroy()		override;

private:
	int64_t	m_timeOffset;
};

