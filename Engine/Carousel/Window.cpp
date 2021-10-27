#include "Window.h"
#include "bgfx_utils.h"

uint32_t Window::width = 1280;
uint32_t Window::height = 720;

Window::~Window() {
    shutdown();
}

int Window::init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) {
    Args args(_argc, _argv);

    m_width     = _width;
    m_height    = _height;
    m_debug     = BGFX_DEBUG_NONE;
    m_reset     = BGFX_RESET_VSYNC;

    bgfx::Init init;
    init.type = args.m_type;
    init.vendorId = args.m_pciId;
    init.resolution.width = m_width;
    init.resolution.height = m_height;
    init.resolution.reset = m_reset;
    bgfx::init(init);

    bgfx::setDebug(m_debug);

    bgfx::setViewClear(
        RENDER_PASS_SHADING,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x303030ff,
        1.0f,
        0
    );
    return 0;
}

void Window::update() {
    Window::width = m_width;
    Window::height = m_height;
}

void Window::shutdown() {
}