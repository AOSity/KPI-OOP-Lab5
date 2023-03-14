#pragma once
#include <GLFW/glfw3.h>

void ApplySettings(GLFWwindow* window);
void ApplyCallbacks(GLFWwindow* window);
void WindowSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
