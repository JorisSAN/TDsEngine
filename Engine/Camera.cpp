#include "Camera.h"
#include "Window.h"
#include <bx/math.h>

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
    Component::update();
    float*  cameraComponentPosition  = getPosition();
    float*  ActorPosition            = owner.getWorldPosition();
    float   cameraPosition[3];
    cameraPosition[0] = cameraComponentPosition[0] + ActorPosition[0];
    cameraPosition[1] = cameraComponentPosition[1] + ActorPosition[1];
    cameraPosition[2] = cameraComponentPosition[2] + ActorPosition[2];
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
    width = Window::width;
    height = Window::height;
    bx::mtxProj(proj, fov, width / height, nearPlan, farPlan, bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
    bgfx::setViewTransform(0, view, proj);
}

void Camera::destroy() {
}