#include "renderer.h"

namespace ED {
    Renderer::Renderer() {
        // NOTE: Initializing glfw
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    // NOTE: Creating glfw window object
    void Renderer::Create_window() {
        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
        if (window == NULL) {
            // TODO: Convert to log
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        this->window = window;
    }

    bool Renderer::Init_glad() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            // TODO: Convert to log
            std::cout << "Failed to initialize GLAD" << std::endl;
            return 0;
        }
        return 1;
    }

    void Renderer::Viewport(int x, int y, int w, int h) {
        glViewport(x, y, w, h);
    }

    // NOTE: if a user resizes the window the viewport should be adjusted as well
    // NOTE: CALLBACK function with lamda
    void Renderer::framebuffer_size_callback() {
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
    }
}  // namespace ED