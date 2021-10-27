#pragma once
#include "common.h"

#define RENDER_PASS_SHADING 0  // Default forward rendered geo with simple shading

class Window
{
public:
	~Window();

	int init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height);
	void update();
	void shutdown();

	uint32_t& getWidth()	{ return m_width;	 }
	uint32_t& getHeight()	{ return m_height;	 }
	uint32_t& getDebug()	{ return m_debug;	 }
	uint32_t& getReset()	{ return m_reset;	 }

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	static uint32_t width;
	static uint32_t height;
};

