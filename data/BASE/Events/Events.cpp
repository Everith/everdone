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
			break;
		}
		case WM_KILLFOCUS: {
			break;
		}
		case WM_KEYDOWN: {
			break;
		}
		case WM_MOUSEMOVE: {
			break;
		}
		case WM_GETMINMAXINFO: {
			break;
		}
		case WM_ACTIVATE: {
			break;
		}
		case WM_ENABLE: {
			break;
		}
		case WM_QUIT: {
			break;
		}
		case WM_DESTROY: {
			break;
		}
		case WM_CLOSE: {
			//PostQuitMessage(69);
			break;
		}
		case WM_MOVING: {
			break;
		}
		case WM_ACTIVATEAPP: {
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
