#pragma once
// Vulkan
#include <vulkan/vulkan.h>

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
        Renderer();
        ~Renderer();
    };
}  // namespace ED