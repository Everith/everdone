//#define WINDOWS_PLATFORM
//#define LINUX_PLATFORM

#include "defines.h"
#include "core.h"

#include "platform/platform.h"
#include "game.h"

#ifdef WINDOWS_PLATFORM
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow) {
    std::cout << "Hello World" << std::endl;
    
    Everith::platform p("Everdone",0,0,1280,1024);
    //Everith::platform p();
    Everith::Game g(&p);
    g.loop(); //NOTE game loop
    
    return 0;
}
#endif

#ifdef LINUX_PLATFORM
int main(){
	std::cout << "Hello world!";
	return 0;
}
#endif
