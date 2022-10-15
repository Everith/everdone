#pragma once
// Vulkan
#include <vulkan/vulkan.h>
// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../defines.h"

#if WINDOWS_PLATFORM
#include <windows.h>
#include <windowsx.h>  // param input extraction
#include <stdlib.h>
// Vulcan
#include <vulkan/vulkan_win32.h>
#endif
#if LINUX_PLATFORM
#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>  // sudo apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>  // sudo apt-get install libxkbcommon-x11-dev
#include <sys/time.h>
#endif

namespace ED {
    class Renderer {
       public:
        GLFWwindow* window = nullptr;

       public:
        Renderer();
        ~Renderer();
        void Create_window();
        bool Init_glad();
        void Viewport(int x, int y, int w, int h);
        void framebuffer_size_callback();
    };
}  // namespace ED