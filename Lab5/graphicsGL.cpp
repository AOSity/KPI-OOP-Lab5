#include "graphicsGL.h"

void ApplySettings(GLFWwindow* window)
{
    glfwSetWindowAspectRatio(window, 16, 9);
    int ScreenWidth, ScreenHeight;
    glfwGetWindowSize(window, &ScreenWidth, &ScreenHeight);
    glViewport(0, 0, ScreenWidth, ScreenHeight);
    glfwMakeContextCurrent(window);
    glOrtho(0, 1920, 0, 1080, -1.0f, 1.0f);
    
}

void ApplyCallbacks(GLFWwindow* window)
{
    glfwSetWindowSizeCallback(window, WindowSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    // WINDOW SETTINGS
    glfwSetWindowAspectRatio(window, 16, 9);
    int ScreenWidth, ScreenHeight;
    glfwGetWindowSize(window, &ScreenWidth, &ScreenHeight);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, ScreenWidth, ScreenHeight);
}
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }
        
}