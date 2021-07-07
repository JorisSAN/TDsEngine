#include "EngineUtils.h"
#include "Window.h"
#include "Cube.h"

#define WNDW_WIDTH 1024
#define WNDW_HEIGHT 768

struct MouseButton
{
    enum Enum
    {
        None,
        Left,
        Middle,
        Right,

        Count
    };
};

struct MouseState
{
    MouseState()
        : m_mx(0)
        , m_my(0)
        , m_mz(0)
    {
        for (uint32_t ii = 0; ii < MouseButton::Count; ++ii)
        {
            m_buttons[ii] = MouseButton::None;
        }
    }

    int32_t m_mx;
    int32_t m_my;
    int32_t m_mz;
    uint8_t m_buttons[MouseButton::Count];
};

int main(void)
{
    // Window creation
    Window window(WNDW_WIDTH, WNDW_HEIGHT);
    // test problems on window's init
    if (window.init() == 1) {
        return 1;
    }

    // Creation of a cube
    Cube cube;
    // Init the cube
    cube.init();

    MouseState mouseState;

    while (!window.windowShouldClose()) {
        // update the window (clear, resize, ...)
        window.update();

        /*
        -------------------------------------------------
            View update
        -------------------------------------------------
        */
        const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
        const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
        float view[16];
        bx::mtxLookAt(view, eye, at);
        float proj[16];
        bx::mtxProj(proj, 60.0f, float(window.getWidth()) / float(window.getHeight()), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);
        /*
        -------------------------------------------------
        */

        // Cube update
        cube.update();

        // Go to the next frame
        bgfx::frame();
    }

    // Always in this order
    // Destroy the cube
    cube.shutdown();
    // Shutdown bgfx
    bgfx::shutdown();
    // Destroy the window
    window.shutdown();

    return 0;
}