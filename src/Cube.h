#pragma once
#include "bgfx/bgfx.h"

class Cube
{
public:
	void init();
	void update();
	void shutdown();

private:
	bgfx::VertexBufferHandle	m_vbh;
	bgfx::IndexBufferHandle		m_ibh;
	bgfx::ProgramHandle			m_program;
	int64_t						m_timeOffset;
};

