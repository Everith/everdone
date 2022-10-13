#include <iostream>
#include "platform/platform.h"
#include "renderer/renderer.h"

int main() {
    // Create window
    ED::platform *p = new ED::platform("Teszt applik", 50, 50, 600, 100);
    if (!p->create_window()) {
        return -1;
    }

    // Create renderer
    ED::Renderer *r = new ED::Renderer();

    while (p->update_window()) {
        std::cout << "Running" << std::endl;

        Sleep(333);  // 60 ish FPS is sleep 33ms
        // NOTE: TOGGLE CONSOL WINDOW
        //  if (IsWindowVisible(GetConsoleWindow()) != FALSE) {
        //      ShowWindow(GetConsoleWindow(), SW_HIDE);
        //  } else {
        //      ShowWindow(GetConsoleWindow(), SW_SHOW);
        //  }
    }

    return 0;
}