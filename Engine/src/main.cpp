#include <iostream>
#include "platform/platform.h"
#include "renderer/renderer.h"

int main()
{
    ED::platform *p = new ED::platform("Teszt applik", 50, 50, 600, 100);
    if (!p->platform_create_window())
    {
        return -1;
    }
    VkContext vkcontext;
    if (!vk_init(&vkcontext, p->m_hwnd))
    {
        std::cout << "VK Init succesful" << std::endl;
    }

    while (p->platform_update_window())
    {
        std::cout << "Running" << std::endl;
        if (!vk_render(&vkcontext))
        {
            return -1;
        }
        Sleep(33); // 60 ish FPS
    }

    return 0;
}

// #include "defines.h"
// #include "core.h"
//
// #include "platform/platform.h"
// #include "game.h"
//
// #ifdef WINDOWS_PLATFORM
// int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow) {
//     //Everith::platform p();
//     Everith::platform p("Everdone",10,30,1900,1000);
//
//     Everith::Game g(&p);
//     g.loop(); //NOTE game loop
//
//     return 0;
// }
// #endif
//
// #ifdef LINUX_PLATFORM
// int main(){
// 	std::cout << "Hello world!";
//
//     Everith::platform p("Everdone",10,30,1900,1000);
//     Everith::Game g(&p);
//     g.loop(); //NOTE game loop
//
// 	return 0;
// }
// #endif
