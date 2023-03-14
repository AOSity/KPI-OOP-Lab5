// #include <iostream>
// using namespace std;

#include "graphicsGL.h"

int main(void)
{
    /* GLFW initialization */
    if (!glfwInit())
        return 1;
    
    /* Create window */
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Lab5 - Horbul Andrii", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    ApplySettings(window);
    ApplyCallbacks(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1, 0, 1);
        glBegin(GL_POLYGON);
        glVertex2f(123, 123);
        glVertex2f(223, 423);
        glVertex2f(23, 323);
        glEnd();

        /* Buffer swap and events processing */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    /* GLFW termination */
    glfwTerminate();
    return 0;
}
