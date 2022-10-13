#include <iostream>
#include "platform/platform.h"
#include "renderer/renderer.h"

int main() {
    ED::platform *p = new ED::platform("Teszt applik", 50, 50, 600, 100);
    if (!p->create_window()) {
        return -1;
    }

    // VkContext vkcontext;
    // if (!vk_init(&vkcontext, p->m_hwnd)) {
    //     std::cout << "VK Init succesful" << std::endl;
    // }

    while (p->update_window()) {
        std::cout << "Running" << std::endl;

        Sleep(333);  // 60 ish FPS is sleep 33ms
        if (::IsWindowVisible(::GetConsoleWindow()) != FALSE) {
            ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
        } else {
            ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
        }
    }

    return 0;
}