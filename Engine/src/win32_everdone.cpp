//#define EVE_PLATFORM_WINDOWS
#include "core.h"

LRESULT CALLBACK EVEEvent(HWND Window, UINT Message, WPARAM Wparam, LPARAM Lparam)
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
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window,&Paint);
			int x = Paint.rcPaint.left;
			int y = Paint.rcPaint.top;
			int width = Paint.rcPaint.right - Paint.rcPaint.left;
			int height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			static DWORD Operation = WHITENESS;
			PatBlt(DeviceContext, x,y,width,height,Operation);
			if (Operation == WHITENESS)
			{
				Operation = BLACKNESS;
			}else{
				Operation = WHITENESS;
			}
			
			break;
		}
		default:
			result = DefWindowProc(Window, Message, Wparam, Lparam);
			break;
		}
		return (result);
	}


int CALLBACK 
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, 
		int nCmdShow) 
{
		//lamda teszt
		// capture | param | func
		//functioin pointer ** func*
//		[]() {};


        
		WNDCLASSA wc = { };
		//wc.cbSize = sizeof(WNDCLASS);
		//wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = EVEEvent;
		//wc.cbClsExtra = 0;
		//wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		//wc.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0);
		//wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		//wc.hbrBackground = 0;
		//wc.lpszMenuName = 0;
		wc.lpszClassName = "Asdasdasd";
		//wc.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0);

		if (RegisterClassA(&wc)) {
			HWND m_hWnd = CreateWindowExA(	0, wc.lpszClassName, "window name here ", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
											CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
											nullptr, nullptr, hInstance, 0);
			if(m_hWnd){
				//ShowWindow(m_hWnd, SW_SHOWDEFAULT);
				//UpdateWindow(m_hWnd);
				for(;;){
					MSG msg;
					BOOL MessageResult = GetMessageA(&msg,0,0,0);
					if (MessageResult > 0)
					{
						TranslateMessage(&msg);
						DispatchMessageA(&msg);
					}else{
						break;
					}
				}
			}	
		}
	return 0;
}
