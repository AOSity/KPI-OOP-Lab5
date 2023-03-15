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

    Group* root = new Group(0,0);
    root->add(new Rectangle(100,150));
    root->add(new Circle(350,100));

    Group* child = new Group(0,0);
    child->add(new Rectangle(1000,250));
    child->add(new Circle(250,700));
    root->add(child);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //root->operation();

        root->operation();

        /* Buffer swap and events processing */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete root;

    /* GLFW termination */
    glfwTerminate();
    return 0;
}
