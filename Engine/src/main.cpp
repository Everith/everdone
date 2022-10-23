#include <iostream>
#include "platform/platform.h"
#include "renderer/renderer.h"

int main() {
    // Create window
    ED::platform *p = new ED::platform("Teszt applik", 50, 50, 600, 100);
    if (!p->Create_window()) {
        return -1;
    }

    // Create renderer OpenGL
    ED::Renderer *r = new ED::Renderer();
    r->Create_window();
    r->Init_glad();
    r->Viewport(0, 0, 800, 600);
    r->framebuffer_size_callback();

    float red = 0.0f;
    bool tog = 0;
    // NOTE: GLFW OpenGL widow loop
    while (!glfwWindowShouldClose(r->window)) {
        r->processInput(r->window);

        glClearColor(red, red / 2, red / 3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(r->window);
        glfwPollEvents();

        if (red >= 1) {
            tog = 1;
        } else if (red <= 0) {
            tog = 0;
        }

        if (tog) {
            red -= 0.01f;
        } else {
            red += 0.01f;
        }
        std::cout << red << std::endl;
        Sleep(33);
    }
    glfwTerminate();

    while (p->update_window()) {
        std::cout << "Running" << std::endl;

        Sleep(33);  // 60 ish FPS is sleep 33ms
        // NOTE: TOGGLE CONSOL WINDOW
        // if (IsWindowVisible(GetConsoleWindow()) != FALSE) {
        //     ShowWindow(GetConsoleWindow(), SW_HIDE);
        // } else {
        //     ShowWindow(GetConsoleWindow(), SW_SHOW);
        // }
    }

    return 0;
}