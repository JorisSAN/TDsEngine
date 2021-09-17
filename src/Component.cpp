#include "Component.h"
#include "MathMatrix.h"
#include "Maths.h"

void Component::destroy() {
    bgfx::destroy(m_ibh);
    bgfx::destroy(m_vbh);
    bgfx::destroy(m_program);
}

void Component::computeTransform() {
    Quaternion rotationResult;
    float axeX[3] = { 1, 0, 0 };
    float axeY[3] = { 0, 1, 0 };
    float axeZ[3] = { 0, 0, 1 };

    rotationResult = Quaternion(axeX, (m_rotation[0] * Maths::pi) / 180);
    rotationResult = Quaternion::concatenate(rotationResult, Quaternion(axeY, (m_rotation[1] * Maths::pi) / 180));
    rotationResult = Quaternion::concatenate(rotationResult, Quaternion(axeZ, (m_rotation[2] * Maths::pi) / 180));

    mathMatrix::createFromQuaternion(m_matrix, rotationResult);
    mathMatrix::translate(m_matrix, m_position[0], m_position[1], m_position[2]);
    mathMatrix::scale(m_matrix, m_scale[0], m_scale[1], m_scale[2]);

    bgfx::setTransform(m_matrix);

    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);

    bgfx::submit(0, m_program);
}

void Component::setPosition(float* pos) {
    for (int i = 0; i < sizeof(m_position) / sizeof(float); i++) {
        m_position[i] = pos[i];
    }
}

void Component::setPosition(float x, float y, float z) {
    m_position[0] = x;
    m_position[1] = y;
    m_position[2] = z;
}

void Component::setScale(float* scl) {
    for (int i = 0; i < sizeof(m_scale) / sizeof(float); i++) {
        m_scale[i] = scl[i];
    }
}

void Component::setScale(float x, float y, float z) {
    m_scale[0] = x;
    m_scale[1] = y;
    m_scale[2] = z;
}

void Component::setRotation(float* rot) {
    for (int i = 0; i < sizeof(m_rotation) / sizeof(float); i++) {
        m_rotation[i] = rot[i];
    }
}

void Component::setRotation(float x, float y, float z) {
    m_rotation[0] = x;
    m_rotation[1] = y;
    m_rotation[2] = z;
}