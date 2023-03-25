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
    GLFWwindow* window = glfwCreateWindow(1280, 720, "OOP-Lab5", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    ApplySettings(window);
    ApplyCallbacks(window);

    Group* root = new Group;
    root->add(new Rectangle(200, 250, 300, 150));
    root->add(new Circle(350, 140, 80));
    root->add(new Circle(1350, 900, 69));

    Group* child = new Group;
    child->add(new Rectangle(1000, 550, 100, 200));
    child->add(new Circle(250, 700, 155));
    root->add(child);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.6, 0.6, 0.6);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(1920, 0);
        glVertex2f(1920, 1080);
        glVertex2f(0, 1080);
        glEnd();

        root->render();

        /* Buffer swap and events processing */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete root;

    /* GLFW termination */
    glfwTerminate();
    return 0;
}
