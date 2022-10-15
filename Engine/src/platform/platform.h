#pragma once
#include "../defines.h"
#if WINDOWS_PLATFORM
#include <windows.h>
#include <windowsx.h>  // param input extraction
#include <stdlib.h>
#endif
#if LINUX_PLATFORM
#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>  // sudo apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>  // sudo apt-get install libxkbcommon-x11-dev
#include <sys/time.h>
#if _POSIX_C_SOURCE >= 199309L
#include <time.h>  // nanosleep
#else
#include <unistd.h>  // usleep
#endif
#endif
namespace ED {
    class platform {
       public:
        platform();
        platform(const char *application_name, i32 x, i32 y, i32 width, i32 height)
            : application_name(application_name), x(x), y(y), width(width), height(height){};
        virtual bool Create_window();

        void shutdown();
        b8 update_window();
        void restore();
        void minimize();
        // void InitNotifyIconData(); // system Tray icon data
        // HWND get_WindowHandle(){return m_hwnd;};
        // HMENU get_Hmenu(){return m_Hmenu;};
        // void set_Hmenu(HMENU hmenu){m_Hmenu = hmenu;};
        // NOTIFYICONDATA* get_notifyIconData(){return &m_notifyIconData;};
        // void *platform_allocate(u64 size, b8 aligned);
        // void platform_free(void *block, b8 aligned);
        // void *platform_zero_memory(void *block, u64 size);
        // void *platform_copy_memory(void *dest, const void *source, u64 size);
        // void *platform_set_memory(void *dest, i32 value, u64 size);
        // void platform_console_write(const char *message, u8 colour);
        // void platform_console_write_error(const char *message, u8 colour);
        // f64 platform_get_absolute_time();
        // void platform_sleep(u64 ms);
        // void get_window_size(uint32_t *width, uint32_t *heigth);
        // char *read_file(char *path, uint32_t *length);
        // void log(const char *msg, TextColor color);
        void exit_application();

       private:
        const char *application_name = "Everdone engine application";
        i32 x = 0;
        i32 y = 0;
        i32 width = 1280;
        i32 height = 1024;
        // NOTIFYICONDATA m_notifyIconData;
       public:
        // bool runnig = true;
        HINSTANCE h_instance = nullptr;
        HWND m_hwnd = nullptr;
        NOTIFYICONDATA m_notifyIconData = {};
        HMENU m_Hmenu = nullptr;
    };
}  // namespace ED