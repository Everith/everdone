#include <vulkan/vulkan.h>
#include <iostream>

int main()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Pong";
	appInfo.pEngineName = "everdone";

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;

	VkInstance vkInstance;
	VkResult result = vkCreateInstance(&instanceInfo, 0, &vkInstance);
	if (result == VK_SUCCESS)
	{
		std::cout << "VK Instance creatnon success" << std::endl;
	}

	return 0;
}

// #include "defines.h"
// #include "core.h"
//
// #include "platform/platform.h"
// #include "game.h"
//
// #ifdef WINDOWS_PLATFORM
// int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow) {
//     //Everith::platform p();
//     Everith::platform p("Everdone",10,30,1900,1000);
//
//     Everith::Game g(&p);
//     g.loop(); //NOTE game loop
//
//     return 0;
// }
// #endif
//
// #ifdef LINUX_PLATFORM
// int main(){
// 	std::cout << "Hello world!";
//
//     Everith::platform p("Everdone",10,30,1900,1000);
//     Everith::Game g(&p);
//     g.loop(); //NOTE game loop
//
// 	return 0;
// }
// #endif
