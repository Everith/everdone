#pragma once
#include <windows.h>
#pragma comment(lib, "Winmm.lib") //Lib file alkalmazása

namespace Sound {
	void playWAV (const wchar_t* filename);
}