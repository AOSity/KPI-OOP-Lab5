#include "logics.h"

#include <GLFW/glfw3.h>
#include <iostream>

/* Composite */

 void Rectangle::operation()
 {
    //std::cout << "Rectangle operation" << std::endl;
	 glColor3f(0, 0.5, 1);
	glBegin(GL_POLYGON);
	glVertex2f(xpos + 50, ypos + 50);
	glVertex2f(xpos - 50, ypos + 50);
	glVertex2f(xpos - 50, ypos - 50);
	glVertex2f(xpos + 50, ypos - 50);
	glEnd();
 }

void Circle::operation()
{
    //std::cout << "Circle operation" << std::endl;
	glColor3f(0.5, 0.5, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 20; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(20);
		float cx = 50 * cosf(theta + 3.1415926f / 2);
		float cy = 50 * sinf(theta + 3.1415926f / 2);

		glVertex2f(xpos + cx, ypos + cy);
	}
	glEnd();
}

Group::~Group()
{
	for (Component* component : components) {
		delete component;
	}
}

void Group::operation()
{
	//std::cout << "Group operation" << std::endl;
	for (Component* component : components) {
		component->operation();
	}
}

void Group::add(Component* component)
{
	components.push_back(component);
}

void Group::remove(Component* component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

Component* Group::getChild(int index)
{
	if (index < 0 || index >= components.size()) {
		return nullptr;
	}
	return components[index];
}
