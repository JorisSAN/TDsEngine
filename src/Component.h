#pragma once
#include "bgfx/bgfx.h"

class Component
{
public:
	virtual void init()		{}
	virtual void update()	{}
	virtual void destroy();

protected:
	bgfx::VertexBufferHandle	m_vbh;
	bgfx::IndexBufferHandle		m_ibh;
	bgfx::ProgramHandle			m_program;
};

