#include "Mesh.h"

StaticMesh::StaticMesh(Actor* ownerP, char* nameP, char* pathP) :
    Component(ownerP, nameP),
    path(pathP)
{

}

StaticMesh::~StaticMesh() {
    Component::~Component();
    destroy();
}

void StaticMesh::init() {
    // Create program from shaders.
    m_program = loadProgram("vs_mesh", "fs_mesh");

    m_mesh = meshLoad(path);
}

void StaticMesh::update() {
    Group group;
    float mtx[16];
    float* transformMatrix = Component::computeTransform();
    for (int i = 0; i < 16; ++i) {
        mtx[i] = transformMatrix[i];
    }
    meshSubmit(m_mesh, 0, m_program, mtx);
}

void StaticMesh::destroy() {
    meshUnload(m_mesh);

    // Cleanup.
    bgfx::destroy(m_program);
}