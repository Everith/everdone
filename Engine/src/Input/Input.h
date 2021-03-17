#pragma once
#include "GLFW/glfw3.h"
#include "../Log/Log.h"
class Input {
private:
    int m_key = 0;
public:
    Input ();
    ~Input ();
    void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
    int get_KeyCallback () { return m_key; };
};