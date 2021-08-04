//#define WINDOWS_PLATFORM
//#define LINUX_PLATFORM

#include "defines.h"
#include "core.h"

#include "platform/platform.h"
#include "game.h"

#ifdef WINDOWS_PLATFORM
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow) {
    //Everith::platform p();
    Everith::platform p("Everdone",10,30,1900,1000);

    Everith::Game g(&p);
    g.loop(); //NOTE game loop
    
    return 0;
}
#endif

#ifdef LINUX_PLATFORM
int main(){
	std::cout << "Hello world!";

    Everith::platform p("Everdone",10,30,1900,1000);
    Everith::Game g(&p);
    g.loop(); //NOTE game loop

	return 0;
}
#endif
