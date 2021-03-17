#include "EveWindow.h"

namespace Everith {
	EveWindow::EveWindow(HINSTANCE hInst, char* pArgs) : args(pArgs), hInstance(hInst)
	{
		// register window class
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = EveEventHandler;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInst;
		//wc.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = 0;
		wc.lpszMenuName = 0;
		wc.lpszClassName = wndClassName;
		//wc.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0);

		//Adjust render client Window size ignoting the borders and menu on top
		RECT wr;
		wr.left = 850;
		wr.right = 400 + wr.left;
		wr.top = 100;
		wr.bottom = 800 + wr.top;
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

		if (RegisterClassEx(&wc)) {
			// WS_SYSMENU | WS_MINIMIZEBOX		---> top right 3 button  ( _ □ X )
			// WS_SIZEBOX									---> sizable border around the window
			hWnd = CreateWindowEx(0, wndClassName, "window name here ", WS_SYSMENU | WS_MINIMIZEBOX | WS_SIZEBOX, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, hInst, this);
		}
		// throw exception if something went terribly wrong
		if (hWnd == nullptr) {
			throw Exception(__FILE__, __LINE__, "Window creation filed, failed to get valid window handle.");
		}

		// show and update
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
	}

	EveWindow::~EveWindow()
	{
		// unregister window class
		UnregisterClass(wndClassName, hInstance);
	}

	//TODO for openning multiple window
	HWND EveWindow::Create(const WindowProps& props)
	{
		WNDCLASS WindowClass = {};
		WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc = this->EveEventHandler;
		WindowClass.hInstance = this->hInstance;
		//WindowClass.hIcon = ;
		WindowClass.lpszClassName = "ClassNameWindow";

		HWND WindowHeandler = CreateWindowEx(
			0,
			WindowClass.lpszClassName,
			props.Title.c_str(),
			METRICS_USEDEFAULT,
			METRICS_USEDEFAULT,
			METRICS_USEDEFAULT,
			props.Width,
			props.Height,
			0,
			0,
			hInstance,
			0);

		return WindowHeandler;
	}
	void EveWindow::setHInstance(HINSTANCE hInstance)
	{
		this->hInstance = hInstance;
	}
	bool EveWindow::IsActive() const
	{
		return GetActiveWindow() == hWnd;
	}
	bool EveWindow::IsMinimized() const
	{
		return IsIconic(hWnd) != 0;
	}
	void EveWindow::ShowMessageBox(const std::string& title, const std::string& message, UINT type) const
	{
		MessageBox(hWnd, message.c_str(), title.c_str(), type);
	}
	bool EveWindow::ProcessMessage()
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				m_QuitMessage = msg.wParam;
				return false;
			}
		}
		return true;
	}
	LRESULT __stdcall EveWindow::EveEventHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return EveEvents.EventCallback(hWnd, msg, wParam, lParam);
	}
}