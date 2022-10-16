#include <iostream>
#include "platform/platform.h"
#include "renderer/renderer.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

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

    // NOTE: GLFW OpenGL widow loop
    while (!glfwWindowShouldClose(r->window)) {
        glfwSwapBuffers(r->window);
        glfwPollEvents();
    }

    while (p->update_window()) {
        std::cout << "Running" << std::endl;

        Sleep(333);  // 60 ish FPS is sleep 33ms
                     // NOTE: TOGGLE CONSOL WINDOW
        // if (IsWindowVisible(GetConsoleWindow()) != FALSE) {
        //     ShowWindow(GetConsoleWindow(), SW_HIDE);
        // } else {
        //     ShowWindow(GetConsoleWindow(), SW_SHOW);
        // }
    }

    return 0;
}