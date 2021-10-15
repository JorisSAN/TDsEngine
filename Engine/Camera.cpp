#include "Camera.h"
#include <bx/math.h>
#include <iostream>

Camera::Camera(Actor* ownerP, char* nameP) :
    Component(ownerP, nameP)
{
}

Camera::~Camera() {
    Component::~Component();
    destroy();
}

void Camera::init() {
}

void Camera::update() {
    float* cameraPosition       = getPosition();
    float* forwardVectorTemp    = getForwardVector();
    float  forwardVector[3];
    forwardVector[0] = forwardVectorTemp[0];
    forwardVector[1] = forwardVectorTemp[1];
    forwardVector[2] = forwardVectorTemp[2];

    const bx::Vec3 eye = 
    {   
        cameraPosition[0],
        cameraPosition[1],
        cameraPosition[2] 
    };

    const bx::Vec3 at = 
    {   
        eye.x + forwardVector[0], 
        eye.y + forwardVector[1],  
        eye.z + forwardVector[2] 
    };

    float view[16];
    bx::mtxLookAt(view, eye, at);

    float proj[16];
    bx::mtxProj(proj, fov, (float)width / (float)height, nearPlan, farPlan, bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
    bgfx::setViewTransform(0, view, proj);
}

void Camera::destroy() {
}