//#define EVE_PLATFORM_WINDOWS
#include "Core.h"
#ifdef WINDOWS_PLATFORM
int CALLBACK 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  // lamda teszt
  // capture | param | func
  // functioin pointer ** func*
  //		[]() {};


  return 0;
}
#endif

#ifdef LINUX_PLATFORM
int main(){
	std::cout << ("Hello world!");
	return 0;
}
#endif
