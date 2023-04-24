#include "graphicsGL.h"

Screen* rootPtr = nullptr;

/* Callbacks */
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
	if (action == GLFW_PRESS)
	{
		double xpos, ypos;
		GetCursorPosition(window, &xpos, &ypos);
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			return;
		case GLFW_KEY_1:
			rootPtr->backup();
			rootPtr->add(new Rectangle(xpos, ypos, 150, 100));
			return;
		case GLFW_KEY_2:
			rootPtr->backup();
			rootPtr->add(new Circle(xpos, ypos, 70));
			return;
		case GLFW_KEY_3:
			rootPtr->backup();
			rootPtr->add(new Rectangle(xpos, ypos, 110, 110, 0, 1, 0.5));
			return;
		case GLFW_KEY_4:
			rootPtr->backup();
			rootPtr->add(new Circle(xpos, ypos, 55, 0.6, 0, 0.45));
			return;
		case GLFW_KEY_Q:
			rootPtr->eraseSelection();
			return;
		case GLFW_KEY_R:
			rootPtr->backup();
			rootPtr->eraseComponents();
			return;
		case GLFW_KEY_E:
			rootPtr->backup();
			rootPtr->eraseSelected();
			return;
		case GLFW_KEY_G:
			rootPtr->backup();
			rootPtr->groupSelected();
			return;
		case GLFW_KEY_C:
			rootPtr->copySelected();
			rootPtr->eraseSelection();
			return;
		case GLFW_KEY_V:
			rootPtr->backup();
			rootPtr->pasteOnCursor(xpos, ypos);
			return;
		case GLFW_KEY_X:
			rootPtr->backup();
			rootPtr->copySelected();
			rootPtr->eraseSelected();
			return;
		case GLFW_KEY_Z:
			rootPtr->undo();
			return;
		default:
			return;
		}
	}
}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;
	GetCursorPosition(window, &xpos, &ypos);

	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			{
				rootPtr->selectOnCursor(xpos, ypos);
			}
			else
			{
				rootPtr->eraseSelection();
				rootPtr->selectOnCursor(xpos, ypos);
			}
			return;
		case GLFW_MOUSE_BUTTON_RIGHT:
			rootPtr->backup();
			rootPtr->moveToCursor(xpos, ypos);
			return;
		default:
			return;
		}
	}
}
/* Callbacks end*/

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