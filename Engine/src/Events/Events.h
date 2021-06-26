#pragma once
#include "../Core.h"
namespace Everith {
	class Events
	{
	public:
		Events();
		~Events();

		static LRESULT CALLBACK EventCallback(HWND Window, UINT Message, WPARAM Wparam, LPARAM Lparam);

	private:

	};
}