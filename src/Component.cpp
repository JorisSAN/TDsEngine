#include "Component.h"
#include <iostream>

void Component::destroy() {
    std::cout << "detruit" << std::endl;
    bgfx::destroy(m_ibh);
    bgfx::destroy(m_vbh);
    bgfx::destroy(m_program);
}