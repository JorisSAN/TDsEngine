#include "Component.h"
#include "MathMatrix.h"
#include "Maths.h"

Component::Component(Actor* ownerP, char* nameP, int updateOrderP) :
    owner(*ownerP),
    updateOrder(updateOrderP)
{
    owner.addComponent(this);
    setName(nameP);
}

Component::~Component() {
    owner.removeComponent(this);
    destroy();
}

float* Component::getWorldPosition() {
    float worldPos[3];
    worldPos[0] = owner.getWorldPosition()[0]+getPosition()[0];
    worldPos[1] = owner.getWorldPosition()[1]+getPosition()[1];
    worldPos[2] = owner.getWorldPosition()[2]+getPosition()[2];
    return worldPos;
}

void Component::destroy() {
    if (isInit) {
        bgfx::destroy(m_ibh);
        bgfx::destroy(m_vbh);
        bgfx::destroy(m_program);
    }
}

float* Component::computeTransform() {
    Quaternion rotationResult;
    float axeX[3] = { 1, 0, 0 };
    float axeY[3] = { 0, 1, 0 };
    float axeZ[3] = { 0, 0, 1 };

    float* worldRotation    = owner.getWorldRotation();
    float* worldPosition    = owner.getWorldPosition();
    float* worldScale       = owner.getWorldScale();

    // Rotation management
    float rotationX = Maths::toRadians(m_rotation[0] + worldRotation[0]);
    float rotationY = Maths::toRadians(m_rotation[1] + worldRotation[1]);
    float rotationZ = Maths::toRadians(m_rotation[2] + worldRotation[2]);

    /* Scale management
    #############################
    */
    float scaledPositionX = m_position[0] * worldScale[0];
    float scaledPositionY = m_position[1] * worldScale[1];
    float scaledPositionZ = m_position[2] * worldScale[2];

    float ScaleX = worldScale[0] * m_scale[0];
    float ScaleY = worldScale[1] * m_scale[1];
    float ScaleZ = worldScale[2] * m_scale[2];

    /*
    #############################
    */

    /* Translation management
    #############################
    */
    float worldRotationX = Maths::toRadians(worldRotation[0]);
    float worldRotationY = Maths::toRadians(worldRotation[1]);
    float worldRotationZ = Maths::toRadians(worldRotation[2]);

    float positionY = scaledPositionY * Maths::cos(worldRotationX) - scaledPositionZ * Maths::sin(worldRotationX);
    float positionZ = scaledPositionZ * Maths::cos(worldRotationX) + scaledPositionY * Maths::sin(worldRotationX);

    float positionX = scaledPositionX * Maths::cos(worldRotationY) + positionZ * Maths::sin(worldRotationY);
    positionZ = positionZ * Maths::cos(worldRotationY) - scaledPositionX * Maths::sin(worldRotationY);

    float tempPosX = positionX;
    float tempPosY = positionY;

    positionX = tempPosX * Maths::cos(worldRotationZ) - tempPosY * Maths::sin(worldRotationZ);
    positionY = tempPosY * Maths::cos(worldRotationZ) + tempPosX * Maths::sin(worldRotationZ);

    positionX += worldPosition[0] * worldScale[0];
    positionY += worldPosition[1] * worldScale[1];
    positionZ += worldPosition[2] * worldScale[2];

    /*
    #############################
    */

    rotationResult = Quaternion(axeX, rotationX);
    rotationResult = Quaternion::concatenate(rotationResult, Quaternion(axeY, rotationY));
    rotationResult = Quaternion::concatenate(rotationResult, Quaternion(axeZ, rotationZ));

    mathMatrix::createFromQuaternion(m_matrix, rotationResult);
    mathMatrix::translate(m_matrix, positionX, positionY, positionZ);
    mathMatrix::scale(m_matrix, ScaleX, ScaleY, ScaleZ);

    bgfx::setTransform(m_matrix);

    if (isInit) {
        bgfx::setVertexBuffer(0, m_vbh);
        bgfx::setIndexBuffer(m_ibh);

        bgfx::submit(0, m_program);
    }

    return m_matrix;
}

void Component::setName(char* nameP)
{
    for (int i = 0; i < sizeof(name) / sizeof(char); i++) {
        name[i] = nameP[i];
        if (nameP[i] == '\0') {
            break;
        }
    }
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

bool Component::isTheComponent(char* nameP)
{
    for (int i = 0; i < sizeof(name) / sizeof(char); ++i) {
        if (name[i] != nameP[i]) { return false; }
        if (name[i] == '\0' && nameP[i] != '\0') { return false; }
        if (name[i] != '\0' && nameP[i] == '\0') { return false; }
        if (name[i] == '\0' && nameP[i] == '\0') { break; }
    }
    return true;
}

float* Component::getForwardVector() {
    float vector[3];
    float* rotation = getRotation();

    float angleX = Maths::toRadians(rotation[2]);
    float angleY = Maths::toRadians(rotation[1]);

    vector[0] = Maths::cos(angleY) * Maths::cos(angleX);
    vector[1] = Maths::sin(angleY) * Maths::cos(angleX);
    vector[2] = Maths::sin(angleX);

    return vector;
}

float* Component::getRightVector() {
    // Get Forward vector
    float forward[3];
    float* forwardVector = getForwardVector();
    forward[0] = forwardVector[0];
    forward[1] = forwardVector[1];
    forward[2] = forwardVector[2];

    // Normalize the Forward vector
    float normalizedForward[3];
    const float* normalizedForwardTemp = Maths::normalize(forward);
    normalizedForward[0] = normalizedForwardTemp[0];
    normalizedForward[1] = normalizedForwardTemp[1];
    normalizedForward[2] = normalizedForwardTemp[2];

    // Get and Normalize the Up vector
    const float up[3] = { 0.0f, 1.0f, 0.0f };
    float normalizedUp[3];
    const float* normalizedUpTemp = Maths::normalize(up);
    normalizedUp[0] = normalizedUpTemp[0];
    normalizedUp[1] = normalizedUpTemp[1];
    normalizedUp[2] = normalizedUpTemp[2];

    // Calculate the Right Vector
    const float* rightTemp = Maths::cross(normalizedForward, normalizedUp);
    float right[3];
    right[0] = rightTemp[0];
    right[1] = rightTemp[1];
    right[2] = rightTemp[2];

    return right;
}