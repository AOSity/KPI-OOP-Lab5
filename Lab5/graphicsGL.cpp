#include "graphicsGL.h"

Screen* rootPtr = nullptr;

void ApplySettings(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    glfwSetWindowAspectRatio(window, 16, 9);
    glOrtho(0, 1920, 0, 1080, -1.0f, 1.0f);
    int ScreenWidth, ScreenHeight;
    glfwGetWindowSize(window, &ScreenWidth, &ScreenHeight);
    glViewport(0, 0, ScreenWidth, ScreenHeight);
    return;
}

void ApplyCallbacks(GLFWwindow* window)
{
    glfwSetWindowSizeCallback(window, WindowSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    return;
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glfwMakeContextCurrent(window);
    int ScreenWidth, ScreenHeight;
    glfwGetWindowSize(window, &ScreenWidth, &ScreenHeight);
    glViewport(0, 0, ScreenWidth, ScreenHeight);
    return;
}
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        double xpos, ypos;
        GetCursorPosition(window, &xpos, &ypos);
        rootPtr->add(new Rectangle(xpos, ypos, 200, 100));
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        double xpos, ypos;
        GetCursorPosition(window, &xpos, &ypos);
        rootPtr->add(new Circle(xpos, ypos, 100));
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        rootPtr->selectedComponents.clear();
    }
    return;
}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        GetCursorPosition(window, &xpos, &ypos);
        rootPtr->selectOnCursor(xpos, ypos);
    }
    return;
}

void GetCursorPosition(GLFWwindow* window, double* xpos, double* ypos)
{
    glfwGetCursorPos(window, xpos, ypos);
    int ScreenWidth, ScreenHeight;
    glfwGetWindowSize(window, &ScreenWidth, &ScreenHeight);

    *xpos *= 1920.f / ScreenWidth;
    *ypos *= 1080.f / ScreenHeight;
    *ypos = 1080 - *ypos;
    return;
}

void SetScreenRoot(Screen* root)
{
    rootPtr = root;
}