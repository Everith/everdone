// #include "platform.h"
// #include "../resource.h"
//
// // Windows platform layer.
// #if WINDOWS_PLATFORM
// #include <wingdi.h>
// #include <iostream>
// #include <stdint.h>
//
// // Clock
// static f64 clock_frequency;
// static LARGE_INTEGER start_time;
//
// namespace Everith {
//
// //TODO make these variables not GLOBAL
// HINSTANCE h_instance=nullptr;
// HWND m_hwnd=nullptr;
//
// NOTIFYICONDATA m_notifyIconData;
// HMENU m_Hmenu=nullptr;
// //###################################
//
//
//
// LRESULT CALLBACK process_message(HWND m_hwnd, u32 msg, WPARAM w_param, LPARAM l_param);
//
// platform::platform(){
// }
//
// b8 platform::platform_startup(){
//     h_instance = GetModuleHandleA(0);
//
//     // Setup and register window class.
//     //HICON icon = LoadIcon(h_instance, IDI_APPLICATION); //WARN redundant lent a sorba beillesytve m'r megvan
//     WNDCLASSA wc;
//     memset(&wc, 0, sizeof(wc));
//     //TODO maybe create here register to taskbar alreadi exist, so dont try to create too early a tray icon ?
//     wc.style = CS_DBLCLKS;  // Get double-clicks
//     wc.lpfnWndProc = process_message;
//     wc.cbClsExtra = 0;
//     wc.cbWndExtra = 0;
//     wc.hInstance = h_instance;
//     /* Use default icon and mouse-pointer */
//     //wc.hIcon  =  LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
//     wc.hIcon  =  LoadIcon (h_instance, MAKEINTRESOURCE(ICO1));
//     //wc.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
//     wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // NULL; // Manage the cursor manually
//     wc.hbrBackground = NULL;                   // Transparent
//     wc.lpszClassName = "Everdone_window_class";
//
//     if (!RegisterClassA(&wc)) {
//         MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
//         return FALSE;
//     }
//
//     // Create window
//     u32 client_x = x;
//     u32 client_y = y;
//     u32 client_width = width;
//     u32 client_height = height;
//
//     u32 window_x = client_x;
//     u32 window_y = client_y;
//     u32 window_width = client_width;
//     u32 window_height = client_height;
//
//     u32 window_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
//     u32 window_ex_style = WS_EX_APPWINDOW;
//
//     // Obtain the size of the border.
//     RECT border_rect = {0, 0, 0, 0};
//     AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);
//
//     // In this case, the border rectangle is negative.
//     window_x += border_rect.left;
//     window_y += border_rect.top;
//
//     // Grow by the size of the OS border.
//     window_width += border_rect.right - border_rect.left;
//     window_height += border_rect.bottom - border_rect.top;
//
//     HWND handle = CreateWindowExA(
//         window_ex_style, "Everdone_window_class", application_name,
//         window_style, window_x, window_y, window_width, window_height,
//         0, 0, h_instance, 0);
//
//     if (handle == 0) {
//         MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
//         return 0;
//     } else {
//         m_hwnd = handle;
//     }
//
//     // Show the window
//     b32 should_activate = 1;  // TODO: if the window should not accept input, this should be false.
//     i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
//     // If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
//     // If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
//     ShowWindow(m_hwnd, show_window_command_flags);
//
//     InitNotifyIconData();
//
//     return 1;
// }
//
// void platform::platform_shutdown() {
//     // Simply cold-cast to the known type.
//     if (m_hwnd) {
//         DestroyWindow(m_hwnd);
//         m_hwnd = 0;
//     }
// }
//
// b8 platform::platform_pump_messages() {
//     MSG message;
//     while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE)) {
//         //OutputDebugStringA(message.message);
//         if (message.message == WM_QUIT || message.message == WM_CLOSE)
//         {
//             return false;
//         }
//         if (69420 == message.message){
//             minimize();
//         }
//
//         TranslateMessage(&message);
//         DispatchMessageA(&message);
//     }
//
//     return true;
// }
//
// void* platform::platform_allocate(u64 size, b8 aligned) {
//     return malloc(size);
// }
//
// void platform::platform_free(void *block, b8 aligned) {
//     free(block);
// }
//
// void* platform::platform_zero_memory(void *block, u64 size) {
//     return memset(block, 0, size);
// }
//
// void* platform::platform_copy_memory(void *dest, const void *source, u64 size) {
//     return memcpy(dest, source, size);
// }
//
// void* platform::platform_set_memory(void *dest, i32 value, u64 size) {
//     return memset(dest, value, size);
// }
//
// void platform::platform_console_write(const char *message, u8 colour) {
//     HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
//     // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
//     static u8 levels[6] = {64, 4, 6, 2, 1, 8};
//     SetConsoleTextAttribute(console_handle, levels[colour]);
//     OutputDebugStringA(message);
//     u64 length = strlen(message);
//     LPDWORD number_written = 0;
//     WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
// }
//
// void platform::platform_console_write_error(const char *message, u8 colour) {
//     HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
//     // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
//     static u8 levels[6] = {64, 4, 6, 2, 1, 8};
//     SetConsoleTextAttribute(console_handle, levels[colour]);
//     OutputDebugStringA(message);
//     u64 length = strlen(message);
//     LPDWORD number_written = 0;
//     WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);
// }
//
// f64 platform::platform_get_absolute_time() {
//     LARGE_INTEGER now_time;
//     QueryPerformanceCounter(&now_time);
//     return (f64)now_time.QuadPart * clock_frequency;
// }
//
// void platform::platform_sleep(u64 ms) {
//     Sleep(ms);
// }
//
// //TODO GLOBAL WARIABLES need to clean up later
// BITMAPINFO BitmapInfo;
// void *BitmapMemory;
// int BitmapWidth;
// int BitmapHeight;
//
//
// void ResizeDIBSection(int Width, int Height){
//     if (BitmapMemory)
//     {
//         VirtualFree(BitmapMemory,0,MEM_RELEASE);
//     }
//
//     BitmapWidth = Width;
//     BitmapHeight = Height;
//
//     BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
//     BitmapInfo.bmiHeader.biWidth = BitmapWidth;
//     BitmapInfo.bmiHeader.biHeight = BitmapHeight;
//     BitmapInfo.bmiHeader.biPlanes = 1;
//     BitmapInfo.bmiHeader.biBitCount = 32; //bits per pixel needed 3x8bit(RGB) + 8bit padding
//     BitmapInfo.bmiHeader.biCompression = BI_RGB;
//     // BitmapInfo.bmiHeader.biSizeImage = 0;
//     // BitmapInfo.bmiHeader.biXPelsPerMeter = 0;
//     // BitmapInfo.bmiHeader.biYPelsPerMeter = 0;
//     // BitmapInfo.bmiHeader.biClrUsed = 0;
//     // BitmapInfo.bmiHeader.biClrImportant = 0;
//
//     int BytesPerPixel = 4;
//     size_t BitmapMemorySize = (Width*Height)*BytesPerPixel;
//     BitmapMemory = VirtualAlloc(0, BitmapMemorySize,MEM_COMMIT, PAGE_READWRITE);
//
//     int Pitch = Width*BytesPerPixel;
//     u8* Row=(u8*)BitmapMemory;
//     for (int y = 0; y < BitmapHeight; ++y)
//     {
//         u8 *Pixel = (u8*)Row;
//         for (int x = 0; x < BitmapWidth; ++x)
//         {
//             //Pixels in memory RGBX Litle Endien
//             *Pixel = (u8)x;
//             ++Pixel;
//
//             *Pixel = (u8)y;
//             ++Pixel;
//
//             *Pixel = 0;
//             ++Pixel;
//
//             *Pixel = 0;
//             ++Pixel;
//         }
//         Row += Pitch;
//     }
//
//
// }
//
// void EvEUpdateWindow(HDC DeviceContext,RECT *WindowRect, int x,int y,int width,int height){
//     int WindowWidth = WindowRect->right - WindowRect->left;
//     int WindowHeight = WindowRect->bottom - WindowRect->top;
//     StretchDIBits(DeviceContext,
//                 //  x, y, width, height,
//                 //  x, y, width, height,
//                  0, 0, BitmapWidth, BitmapHeight,
//                  0, 0, WindowWidth, WindowHeight,
//                  BitmapMemory,
//                  &BitmapInfo,
//                  DIB_RGB_COLORS,SRCCOPY);
// }
//
// void platform::minimize(){
//     // hide the main window
//     OutputDebugStringW(L"\nminimize()");
//     ShowWindow(m_hwnd, SW_HIDE);
// }
//
// void platform::restore(){
//     ShowWindow(m_hwnd, SW_SHOW);
// }
//
// void platform::InitNotifyIconData(){
//     memset( &m_notifyIconData, 0, sizeof( NOTIFYICONDATA ) ) ;
//
//     const char* szTIP = "Hahaahah traz name here";
//
//     m_notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
//     m_notifyIconData.hWnd = m_hwnd;
//     m_notifyIconData.uID = ID_TRAY_APP_ICON;
//     m_notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
//     m_notifyIconData.uCallbackMessage = WM_SYSICON; //Set up our invented Windows Message
//     m_notifyIconData.hIcon = (HICON)LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1) ) ;
//     strncpy(m_notifyIconData.szTip, szTIP, sizeof(szTIP)); //TODO maybe szTIP should be a variable not a const string letters
// }
//
// LRESULT process_message(HWND window, u32 msg, WPARAM w_param, LPARAM l_param) {
//     platform p;
//     switch (msg) {
//         case WM_CREATE:{
//             OutputDebugStringW(L"\nWM_CREATE");
//             ShowWindow(m_hwnd, SW_HIDE);
//             m_Hmenu = CreatePopupMenu();
//             AppendMenu(m_Hmenu, MF_STRING, ID_TRAY_EXIT,  TEXT( "Exit" ) );
//         }break;
//         case WM_ACTIVATE:{
//             OutputDebugStringW(L"\nWM_ACTIVATE\n");
//             Shell_NotifyIcon(NIM_ADD, &m_notifyIconData);
//         }break;
//         case WM_SYSCOMMAND:{
//             OutputDebugStringW(L"\nWM_SYSCOMMAND");
//             /*
//             In WM_SYSCOMMAND messages, the four low-order bits of the wParam parameter
//             are used internally by the system. To obtain the correct result when testing the value of wParam,
//             an application must combine the value 0xFFF0 with the wParam value by using the bitwise AND operator.
//             */
//
//             switch( w_param & 0xFFF0 )
//             {
//             case SC_MINIMIZE:
//             case SC_CLOSE:
//                 OutputDebugStringW(L"\nSC_CLOSE 69420");
//                 break;
//             }
//         }break;
//         case WM_SYSICON:{
//             OutputDebugStringW(L"\nWM_SYSICON");
//
//             switch(w_param){
//             case ID_TRAY_APP_ICON:{
//                 OutputDebugStringW(L"\nID_TRAY_APP_ICON");
//                 SetForegroundWindow(m_hwnd);
//             }break;
//             }
//
//             if (l_param == WM_LBUTTONUP){
//                 //TODO restore
//             }
//             else if (l_param == WM_RBUTTONDOWN){
//                 // Get current mouse position.
//                 POINT curPoint ;
//                 GetCursorPos(&curPoint) ;
//                 SetForegroundWindow(m_hwnd);
//
//                 // TrackPopupMenu blocks the app until TrackPopupMenu returns
//                 UINT clicked = TrackPopupMenu(m_Hmenu,TPM_RETURNCMD | TPM_NONOTIFY,curPoint.x,curPoint.y,0,m_hwnd,NULL);
//
//                 SendMessage(m_hwnd, WM_NULL, 0, 0); // send benign message to window to make sure the menu goes away.
//                 if (clicked == ID_TRAY_EXIT){
//                 // quit the application.
//                      Shell_NotifyIcon(NIM_DELETE, &m_notifyIconData);
//                      PostQuitMessage(0);
//                 }
//             }
//         }break;
//         case WM_NCHITTEST:{
//             //OutputDebugStringW(L"\nWM_NCHITTEST");
//             UINT uHitTest = DefWindowProcA(window, msg, w_param, l_param);
//             if(uHitTest == HTCLIENT)
//                 return HTCAPTION;
//             else
//                 return uHitTest;
//         }break;
//         case WM_CLOSE:{
//             OutputDebugStringW(L"\nWM_CLOSE");
//             PostQuitMessage(0);
//             return WM_QUIT;
//         }break;
//         case WM_DESTROY:{
//             OutputDebugStringW(L"\nWM_DESTROY");
//             return WM_QUIT;
//         }break;
//         case WM_SIZE:{
//             RECT clientrect;
//             GetClientRect(window,&clientrect);
//             int width=clientrect.right - clientrect.left;
//             int height=clientrect.bottom-clientrect.top;
//             ResizeDIBSection(width,height);
//         }break;
//         case WM_PAINT:{
//             PAINTSTRUCT Paint;
//             HDC DeviceContext = BeginPaint(window, &Paint);
//             int x = Paint.rcPaint.left;
//             int y = Paint.rcPaint.top;
//             int width = Paint.rcPaint.right;
//             int height = Paint.rcPaint.bottom;
//             RECT ClientRect;
//             GetClientRect(window,&ClientRect);
//             EvEUpdateWindow(DeviceContext,&ClientRect,x,y,width,height);
//             EndPaint(window,&Paint);
//         }break;
//         default:
//             return DefWindowProcA(window, msg, w_param, l_param);
//     }
//     return DefWindowProcA(window, msg, w_param, l_param);
// }
// }
// #endif