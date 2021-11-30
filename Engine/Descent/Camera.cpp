#include "Camera.h"
#include "Timer.h"
#include "Window.h"
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
    float   cameraPosition[3];
    cameraPosition[0] = getPosition()[0] + owner.getWorldPosition()[0];
    cameraPosition[1] = getPosition()[1] + owner.getWorldPosition()[1];
    cameraPosition[2] = getPosition()[2] + owner.getWorldPosition()[2];
    float  forwardVector[3];
    forwardVector[0] = getForwardVector()[0];
    forwardVector[2] = getForwardVector()[1];
    forwardVector[1] = getForwardVector()[2];
    //std::cout << "forward : x : " << forwardVector[0] << " | y : " << forwardVector[1] << " | z : " << forwardVector[2] << std::endl;

    const bx::Vec3 eye = 
    {   
        cameraPosition[0],
        cameraPosition[1],
        cameraPosition[2] 
    };
    //std::cout << "eye : x : " << eye.x << " | y : " << eye.y << " | z : " << eye.z << std::endl;

    const bx::Vec3 at = 
    {   
        eye.x + forwardVector[0], 
        eye.y + forwardVector[1],  
        eye.z + forwardVector[2] 
    };
    //std::cout << "at : x : " << at.x << " | y : " << at.y << " | z : " << at.z << std::endl;

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