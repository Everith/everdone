#include "Events.h"
namespace Everith {
	Events::Events()
	{
	}

	Events::~Events()
	{
	}

	LRESULT Events::EventCallback(HWND Window, UINT Message, WPARAM Wparam, LPARAM Lparam)
	{
		LRESULT result = 0;
		switch (Message)
		{
		case WM_SIZE: {
			EVE_CORE_INFO("WM_SIZE");
			break;
		}
		case WM_KILLFOCUS: {
			EVE_CORE_INFO("WM_KILLFOCUS");
			break;
		}
		case WM_KEYDOWN: {
			EVE_CORE_INFO("WM_KEYDOWN");
			break;
		}
		case WM_MOUSEMOVE: {
			EVE_CORE_INFO("WM_MOUSEMOVE");
			break;
		}
		case WM_GETMINMAXINFO: {
			EVE_CORE_INFO("WM_GETMINMAXINFO");
			break;
		}
		case WM_ACTIVATE: {
			EVE_CORE_INFO("WM_ACTIVATE");
			break;
		}
		case WM_ENABLE: {
			EVE_CORE_INFO("WM_ENABLE");
			break;
		}
		case WM_QUIT: {
			EVE_CORE_INFO("WM_QUIT");
			break;
		}
		case WM_DESTROY: {
			EVE_CORE_INFO("WM_DESTROY");
			break;
		}
		case WM_CLOSE: {
			EVE_CORE_INFO("WM_CLOSE");
			//PostQuitMessage(69);
			break;
		}
		case WM_MOVING: {
			EVE_CORE_INFO("Moving window");
			break;
		}
		case WM_ACTIVATEAPP: {
			EVE_CORE_INFO("WM_ACTIVATEAPP");
			break;
		}
		case WM_PAINT: {
			//EVE_CORE_INFO("WM_PAINT ---> call renderer");
			break;
		}
		default:
			result = DefWindowProc(Window, Message, Wparam, Lparam);
			break;
		}
		return (result);
	}
}