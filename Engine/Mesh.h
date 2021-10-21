#pragma once
#include "Component.h"
#include "bgfx_utils.h"

class StaticMesh : public Component
{
public:
	StaticMesh(Actor* ownerP, char* nameP, char* pathP);
	virtual ~StaticMesh();
	StaticMesh() = delete;
	StaticMesh(const StaticMesh&) = delete;
	StaticMesh& operator=(const StaticMesh&) = delete;

	void init()		override;
	void update()	override;
	void destroy()	override;

private:
	Mesh* m_mesh;
	char* path;
};

