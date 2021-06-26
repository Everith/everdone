#pragma once
#include "../../Core.h"

namespace Everith {
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		// WindowProps(const std::string& title = "Everith Engine",
		// 	unsigned int width = 1280,
		// 	unsigned int height = 720)
		// 	: Title(title), Width(width), Height(height)
		// {
		// }
	};

	// Interface representing a desktop system based Window
	class Window {
	public:
		virtual Window* Create (const WindowProps& props = WindowProps()) =0;
		virtual ~Window () {}
	};
}
