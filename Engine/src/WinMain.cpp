#include "ConsolApp.h"
#include "Window/Window.h"
#include "Window/Windows/EveWindow.h"
#include "Events/Events.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//Console commands conversion to string
	std::string arg = lpCmdLine;
	//ConsolApp
	if (arg.length() > 0) {
		Everith::ConsolApp Consol;
		static Everith::Log l;
		Everith::Config c;
		c.check();

		//TODO: asdasd
		//lamda teszt#########################################################################################
		// capture | param | func
		//functioin pointer ** func*

		[]() {};

		//#########################################################################################

		EVE_CORE_INFO("Logger INFO");
		EVE_CORE_PASS("Logger PASS");
		EVE_CORE_WARN("Logger Warning");
		EVE_CORE_ERROR("Logger Error");
		EVE_CORE_FATAL("Logger Fatal");
		EVE_INFO("Client side Logger Info");

		Consol.Commands(arg);

#ifdef EVE_DEBUG //System console pause
		system("pause");
#endif //EVE_DEBUG
		return 0; //Exit application
	}
	else { // GUI App
#ifdef EVE_DEBUG
		Everith::ConsolApp Consol;
#endif // DEBUG
		static Everith::Log l;
		Everith::Config c;
		c.check();

		Everith::WindowProps props;
		props.Height = 100;
		props.Width = 200;
		props.Title = "Main window";
		try {
			Everith::EveWindow wnd(hInstance, (char*)lpCmdLine);
			while (wnd.ProcessMessage()) {
				//EVE_CORE_PASS("Logger PASS");
			}
			return wnd.m_QuitMessage;
		}
		catch (const Everith::EveWindow::Exception& e) {
			EVE_FATAL(e.GetFullMessage());
		}
#ifdef EVE_DEBUG //System console pause
		system("pause");
#endif //EVE_DEBUG
		// wParam is the value passed to PostQuitMessage
	}
	return -1;
}