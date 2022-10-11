#include "platform.h"
// #include "../resource.h"
// Windows platform layer.

#if WINDOWS_PLATFORM
#include <wingdi.h>
#include <iostream>
#include <stdint.h>
// Clock
static f64 clock_frequency;
static LARGE_INTEGER start_time;
namespace ED
{

    LRESULT CALLBACK process_message(HWND m_hwnd, u32 msg, WPARAM w_param, LPARAM l_param);
    platform::platform()
    {
    }
    bool platform::create_window()
    {
        h_instance = GetModuleHandleA(0);
        // Setup and register window class.
        WNDCLASSA wc = {};
        // memset(&wc, 0, sizeof(wc)); // allocating memory for wc class TODO:maybe later
        wc.style = CS_DBLCLKS; // Get double-clicks
        wc.lpfnWndProc = process_message;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = h_instance;
        // wc.hIcon  =  LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
        // wc.hIcon = LoadIcon(h_instance, MAKEINTRESOURCE(ICO1));
        // wc.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
        wc.hCursor = LoadCursor(NULL, IDC_ARROW); // NULL; // Manage the cursor manually
        wc.hbrBackground = NULL;                  // Transparent
        wc.lpszClassName = "Everdone_window_class";
        if (!RegisterClassA(&wc))
        {
            MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            return FALSE;
        }
        // Get window size and border
        u32 window_x = x;
        u32 window_y = y;
        u32 window_width = width;
        u32 window_height = height;
        u32 window_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
        u32 window_ex_style = WS_EX_APPWINDOW;
        // Obtain the size of the border.
        RECT border_rect = {0, 0, 0, 0};
        AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);
        // In this case, the border rectangle is negative.
        window_x += border_rect.left;
        window_y += border_rect.top;
        // Grow by the size of the OS border.
        window_width += border_rect.right - border_rect.left;
        window_height += border_rect.bottom - border_rect.top;

        // Create window
        HWND handle = CreateWindowExA(
            window_ex_style, "Everdone_window_class", application_name,
            window_style, window_x, window_y, window_width, window_height,
            0, 0, h_instance, 0);
        if (handle == 0)
        {
            MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return 0;
        }
        else
        {
            m_hwnd = handle;
        }
        // Show the window
        b32 should_activate = 1; // TODO: if the window should not accept input, this should be false.
        i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
        // If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
        // If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
        ShowWindow(m_hwnd, show_window_command_flags);
        // InitNotifyIconData();
        return 1;
    }
    void platform::shutdown()
    {
        // Simply cold-cast to the known type.
        if (m_hwnd)
        {
            DestroyWindow(m_hwnd);
            m_hwnd = 0;
        }
    }
    b8 platform::update_window()
    {
        MSG message;
        while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        {
            // OutputDebugStringA(message.message);
            if (message.message == WM_QUIT || message.message == WM_CLOSE)
            {
                return false;
            }
            if (69420 == message.message)
            {
                minimize();
            }
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
        return true;
    }
    //    void *platform::platform_allocate(u64 size, b8 aligned)
    //    {
    //        return malloc(size);
    //    }
    //    void platform::platform_free(void *block, b8 aligned)
    //    {
    //        free(block);
    //    }
    //    void *platform::platform_zero_memory(void *block, u64 size)
    //    {
    //        return memset(block, 0, size);
    //    }
    //    void *platform::platform_copy_memory(void *dest, const void *source, u64 size)
    //    {
    //        return memcpy(dest, source, size);
    //    }
    //    void *platform::platform_set_memory(void *dest, i32 value, u64 size)
    //    {
    //        return memset(dest, value, size);
    //    }
    //    void platform::platform_console_write(const char *message, u8 colour)
    //    {
    //        HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //        // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    //        static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    //        SetConsoleTextAttribute(console_handle, levels[colour]);
    //        OutputDebugStringA(message);
    //        u64 length = strlen(message);
    //        LPDWORD number_written = 0;
    //        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
    //    }
    //    void platform::platform_console_write_error(const char *message, u8 colour)
    //    {
    //        HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    //        // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    //        static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    //        SetConsoleTextAttribute(console_handle, levels[colour]);
    //        OutputDebugStringA(message);
    //        u64 length = strlen(message);
    //        LPDWORD number_written = 0;
    //        WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);
    //    }
    //    f64 platform::platform_get_absolute_time()
    //    {
    //        LARGE_INTEGER now_time;
    //        QueryPerformanceCounter(&now_time);
    //        return (f64)now_time.QuadPart * clock_frequency;
    //    }
    //    void platform::platform_sleep(u64 ms)
    //    {
    //        Sleep(ms);
    //    }
    void platform::minimize()
    {
        // hide the main window
        OutputDebugStringW(L"\nminimize()");
        ShowWindow(m_hwnd, SW_HIDE);
    }
    void platform::restore()
    {
        ShowWindow(m_hwnd, SW_SHOW);
    }

    //    void platform::InitNotifyIconData()
    //    {
    //        memset(&m_notifyIconData, 0, sizeof(NOTIFYICONDATA));
    //        m_notifyIconData.cbSize = sizeof(NOTIFYICONDATA); // notifyIconData size
    //        m_notifyIconData.hWnd = m_hwnd; // window handler
    //        m_notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; // functionality flags
    //        m_notifyIconData.uID = ID_TRAY_APP_ICON; // ? what is this
    //        m_notifyIconData.hIcon = (HICON)LoadImageA(NULL, "anime.ico", IMAGE_ICON, -1, 0, LR_LOADFROMFILE | LR_SHARED); // load tray icon
    //        m_notifyIconData.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1)); // ? MAKEIBTERSOURCE() ?
    //        strncpy(m_notifyIconData.szTip, "ToolTip for tray icon", sizeof(szTIP)); // hover tool tip
    //        memcpy(nid.szTip, "Tool Tip for try icon.", 127);                                                // max size is 128 this is tray hover tool tip
    //        memcpy(nid.szInfoTitle, "Info title.", 63);                                                      // max size is 64
    //        memcpy(nid.szInfo, "Info baloon.", 264);                                                         // max size is 64 this is a notification windows context text in screen right bottom corner
    //        Shell_NotifyIconA(NIM_ADD, &nid);    // NOTE: add system tray icon to startmenu
    //        m_notifyIconData.uCallbackMessage = WM_SYSICON; //? Set up our invented Windows Message
    // Shell_NotifyIconA(NIM_ADD, &nid); // show notificon on start menu
    // Shell_NotifyIconA(NIM_DELETE, &nid); // remove notificon from stert menu
    //    }

    LRESULT process_message(HWND window, u32 msg, WPARAM w_param, LPARAM l_param)
    {
        platform p;
        switch (msg)
        {
        case WM_SYSCOMMAND:
        {
            OutputDebugStringW(L"\nWM_SYSCOMMAND");
            /*
            In WM_SYSCOMMAND messages, the four low-order bits of the wParam parameter
            are used internally by the system. To obtain the correct result when testing the value of wParam,
            an application must combine the value 0xFFF0 with the wParam value by using the bitwise AND operator.
            */
            switch (w_param & 0xFFF0)
            {
            case SC_MINIMIZE:
            case SC_CLOSE:
                OutputDebugStringW(L"\nSC_CLOSE 69420");
                break;
            }
        }
        break;
        case WM_CLOSE:
        {
            OutputDebugStringW(L"\nWM_CLOSE");
            PostQuitMessage(0);
            return WM_QUIT;
        }
        break;
        case WM_DESTROY:
        {
            OutputDebugStringW(L"\nWM_DESTROY");
            return WM_QUIT;
        }
        break;
        default:
            return DefWindowProcA(window, msg, w_param, l_param);
        }
        return DefWindowProcA(window, msg, w_param, l_param);
    }
}
#endif