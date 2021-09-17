#pragma once
#include "bgfx/bgfx.h"
#include"Quaternion.h"

class Component
{
public:
	virtual void init()		{}
	virtual void update()	{}
	virtual void destroy();

	void computeTransform();

	void	setPosition(float* pos);
	void	setPosition(float x, float y, float z);
	void	setScale(float* scl);
	void	setScale(float x, float y, float z);
	void	setRotation(float* rot);
	void	setRotation(float x, float y, float z);

	float* getPosition()	{ return m_position;	}
	float* getScale()		{ return m_scale;		}
	float* getRotation()	{ return m_rotation;	}

protected:
	bgfx::VertexBufferHandle	m_vbh;
	bgfx::IndexBufferHandle		m_ibh;
	bgfx::ProgramHandle			m_program;
	float						m_matrix[16];

private:
	float		m_position[3] = { 0, 0, 0 };
	float		m_scale[3] =	{ 1, 1, 1 };
	float		m_rotation[3] = { 0, 0, 0 }; // angle in degrees
	Quaternion	m_rotation_by_quaternion;
};