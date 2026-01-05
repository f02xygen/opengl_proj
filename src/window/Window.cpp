#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"

GLFWwindow* Window::window;
int Window::initialize(int width, int height, const char* title) {
    // Инициализация GLFW
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Создание окна
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    int display_width, display_height;
    glfwGetFramebufferSize(window, &display_width, &display_height);

    // Инициализация GLEW (после создания контекста!)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    glViewport(0, 0, display_width, display_height);

    return 0;
}

void Window::terminate() {
    glfwTerminate();
}

bool Window::isShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::setShouldClode(bool flag) {
    glfwSetWindowShouldClose(window, flag);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}