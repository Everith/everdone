#include "ConsolApp.h"
#include <Windows.h>

#include "Log/Log.h"
#include "Books/FictionLive.h"

namespace Everith {
	ConsolApp::ConsolApp()
	{
		FILE* fp;
		FILE* conin, * conout;
		setlocale(LC_ALL, "");
		AllocConsole();
		SetConsoleTitle("Everith Consol");
		freopen_s(&conin, "conin$", "r", stdin);
		freopen_s(&conout, "conout$", "w", stdout);
		freopen_s(&conout, "conout$", "w", stderr);
		MoveWindow(GetConsoleWindow(), 10, 60, 800, 900, TRUE); // x, y, width, height
	}

	ConsolApp::~ConsolApp()
	{
		FreeConsole();
	}

	void ConsolApp::Commands(std::string command)
	{
		//Wallpaper w;

		//if (command == "-wp-rate") {
		//    EVE_CORE_INFO (" -wp-rate Háttérképek váloagatása a Válogatni/Dektop mappábó");
		//    w.rate_wallpappers ();
		//}
		if (command == "-book") {
			EVE_CORE_INFO(" -book fiction.live converter");
			try
			{
				FictionLive f1;
				f1.ConvertFile("data\\books\\fiction01.txt", "1");
				FictionLive f2;
				f2.ConvertFile("data\\books\\fiction02.txt", "2");
				FictionLive f3;
				f3.ConvertFile("data\\books\\fiction03.txt", "3");
				FictionLive f4;
				f4.ConvertFile("data\\books\\fiction04.txt", "4");
				FictionLive f5;
				f5.ConvertFile("data\\books\\fiction05.txt", "5");
				FictionLive f6;
				f6.ConvertFile("data\\books\\fiction06.txt", "6");
				FictionLive f7;
				f7.ConvertFile("data\\books\\fiction07.txt", "7");
				FictionLive f8;
				f8.ConvertFile("data\\books\\fiction08.txt", "8");
				FictionLive f9;
				f9.ConvertFile("data\\books\\fiction09.txt", "9");
				FictionLive f10;
				f10.ConvertFile("data\\books\\fiction10.txt", "10");
				FictionLive f11;
				f11.ConvertFile("data\\books\\fiction11.txt", "11");
				FictionLive f12;
				f12.ConvertFile("data\\books\\fiction12.txt", "12");
				FictionLive f13;
				f13.ConvertFile("data\\books\\fiction13.txt", "13");
			}
			catch (const std::exception&)
			{
			}
		}
		//if (command == "-wp 000") {
		//    EVE_CORE_INFO (" -wp parancs elfogadva");
		//    w.setTags (L"000");
		//}
		//if (command == "-wp 002") {
		//    EVE_CORE_INFO (" -wp parancs elfogadva");
		//    w.setTags (L"002");
		//}
		//if (command == "-wp 008") {
		//    EVE_CORE_INFO (" -wp parancs elfogadva");
		//    w.setTags (L"008");
		//}
		//if (command == "-wp-update") {
		//    w.wallpaper_update ();
		//}
		//if (command == "-wp-sort") {
		//    w.sort_wallpaper ();
		//}
		//if (command == "-wp-sort-rips") {
		//    ShowWindow (GetConsoleWindow (), SW_HIDE);
		//    w.SortRips ();
		//}
		if (command == "-test" || command == "-help") {
			EVE_CORE_INFO("Létezö parancsok:");
			EVE_CORE_INFO("   -wp \"1-9\"   --háttér beálítása/változtatása");
			EVE_CORE_INFO("   -wp-update    --háttérképek frissitése");
			EVE_CORE_INFO("   -wp-sort      --háttérképek szelektálása");
			EVE_CORE_INFO("   -wp-rate      --Háttérképek váloagatása a Válogatni/Dektop mappábó");
		}
	}
}