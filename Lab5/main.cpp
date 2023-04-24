#include <iostream>
using namespace std;

#include "graphicsGL.h"
#include "logics.h"

int main(void)
{
    /* GLFW initialization */
    if (!glfwInit())
        return 1;

    /* Create window */
    GLFWwindow* window = glfwCreateWindow(1280, 720, "OOP-Lab5 \"Design Patterns\" by Horbul Andrii", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    ApplySettings(window);
    ApplyCallbacks(window);

    /* root of the backend of the screen */
    Screen root;
    /* connect frontend to the root*/
    SetScreenRoot(&root);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Background */
        glColor3f(0.6, 0.6, 0.6); 
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(1920, 0);
        glVertex2f(1920, 1080);
        glVertex2f(0, 1080);
        glEnd();

        root.render();

        /* Buffer swap and events processing */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    /* GLFW termination */
    glfwTerminate();
    return 0;
}
