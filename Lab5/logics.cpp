#include "logics.h"
#include "GLFW/glfw3.h"

//#include <iostream>

/* Composite pattern */

/* Rectangle implementation */
void Rectangle::render()
{
	/* Render rectangle */
	glColor3f(0, 0.5, 1);
	glBegin(GL_POLYGON);
	glVertex2f(xpos + width / 2.0f, ypos + height / 2.0f);
	glVertex2f(xpos - width / 2.0f, ypos + height / 2.0f);
	glVertex2f(xpos - width / 2.0f, ypos - height / 2.0f);
	glVertex2f(xpos + width / 2.0f, ypos - height / 2.0f);
	glEnd();
	/* Render outline */
	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xpos + width / 2.0f, ypos + height / 2.0f);
	glVertex2f(xpos - width / 2.0f, ypos + height / 2.0f);
	glVertex2f(xpos - width / 2.0f, ypos - height / 2.0f);
	glVertex2f(xpos + width / 2.0f, ypos - height / 2.0f);
	glEnd();
}
void Rectangle::borders(float* xmin, float* xmax, float* ymin, float* ymax)
{
	*xmin = xpos - width / 2.0f;
	*xmax = xpos + width / 2.0f;
	*ymin = ypos - height / 2.0f;
	*ymax = ypos + height / 2.0f;
}
Component* Rectangle::onCursor(double cursorX, double cursorY)
{
	if (cursorX <= xpos + width / 2.f && cursorX >= xpos - width / 2.f
		&& cursorY <= ypos + height / 2.f && cursorY >= ypos - height / 2.f)
	{
		return this;
	}
	return nullptr;
}
void Rectangle::renderSelection()
{
	/* Render selection outline */
	glColor3f(1, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xpos + width / 2.0f, ypos + height / 2.0f);
	glVertex2f(xpos - width / 2.0f, ypos + height / 2.0f);
	glVertex2f(xpos - width / 2.0f, ypos - height / 2.0f);
	glVertex2f(xpos + width / 2.0f, ypos - height / 2.0f);
	glEnd();
}
/* Rectangle implementation ends */

/* Circle implementation */
void Circle::render()
{
	/* Render circle*/
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 50; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(50);
		float cx = radius * cosf(theta + 3.1415926f / 2);
		float cy = radius * sinf(theta + 3.1415926f / 2);

		glVertex2f(xpos + cx, ypos + cy);
	}
	glEnd();
	/* Render outline*/
	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 50; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(50);
		float cx = radius * cosf(theta + 3.1415926f / 2);
		float cy = radius * sinf(theta + 3.1415926f / 2);

		glVertex2f(xpos + cx, ypos + cy);
	}
	glEnd();
}
void Circle::borders(float* xmin, float* xmax, float* ymin, float* ymax)
{
	*xmin = xpos - radius;
	*xmax = xpos + radius;
	*ymin = ypos - radius;
	*ymax = ypos + radius;
}
Component* Circle::onCursor(double cursorX, double cursorY)
{
	double CenterCursorDistance = sqrt(pow(xpos - cursorX, 2) + pow(ypos - cursorY, 2));
	if (CenterCursorDistance <= radius)
	{
		return this;
	}
	return nullptr;
}
void Circle::renderSelection()
{
	/* Render selection outline */
	glColor3f(1, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 50; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(50);
		float cx = radius * cosf(theta + 3.1415926f / 2);
		float cy = radius * sinf(theta + 3.1415926f / 2);

		glVertex2f(xpos + cx, ypos + cy);
	}
	glEnd();
}
/* Circle implementation ends */

/* Group implementation */
Group::~Group()
{
	for (Component* component : components)
	{
		delete component;
	}
}
void Group::borders(float* xmin, float* xmax, float* ymin, float* ymax)
{
	*xmin = this->xmin;
	*xmax = this->xmax;
	*ymin = this->ymin;
	*ymax = this->ymax;
}
void Group::render()
{
	for (Component* component : components)
	{
		component->render();
	}
	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();
}
void Group::add(Component* component)
{
	components.push_back(component);
	float cxmin, cxmax, cymin, cymax;
	component->borders(&cxmin, &cxmax, &cymin, &cymax);
	if (cxmin < xmin)
	{
		xmin = cxmin;
	}
	if (cxmax > xmax)
	{
		xmax = cxmax;
	}
	if (cymin < ymin)
	{
		ymin = cymin;
	}
	if (cymax > ymax)
	{
		ymax = cymax;
	}
}
void Group::remove(Component* component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}
Component* Group::getChild(int index)
{
	if (index < 0 || index >= components.size())
	{
		return nullptr;
	}
	return components[index];
}
Component* Group::onCursor(double cursorX, double cursorY)
{
	Component* foundComponent = nullptr;
	for (Component* component : components)
	{
		if (component->onCursor(cursorX, cursorY) != nullptr)
		{
			foundComponent = component->onCursor(cursorX, cursorY);
		}
	}
	if (foundComponent != nullptr)
	{
		//std::cout << "Found component: " << foundComponent << std::endl;
		return foundComponent;
	}
	else
	{
		//std::cout << "Nothing found!" << std::endl;
		return nullptr;
	}
}
void Group::eraseComponents()
{
	components.clear();
	xmin = 1921.f;
	xmax = -1.f;
	ymin = 1081.f;
	ymax = -1.f;
}
/* Group implementation ends */

/* Screen implementation */
void Screen::render()
{
	root->render(); renderSelection();
}
void Screen::add(Component* component)
{
	root->add(component);
}
void Screen::remove(Component* component)
{
	root->remove(component);
}
Component* Screen::findOnCursor(double cursorX, double cursorY)
{
	return root->onCursor(cursorX, cursorY);
}
void Screen::selectOnCursor(double cursorX, double cursorY)
{
	Component* selected;
	if ((selected = findOnCursor(cursorX, cursorY)) != nullptr)
	{
		selectedComponents.insert(selected);
	}
}
void Screen::renderSelection()
{
	for (Component* selected : selectedComponents)
	{
		selected->renderSelection();
	}
}
void Screen::eraseComponents()
{
	root->eraseComponents();
}
void Screen::eraseSelection()
{
	selectedComponents.clear();
}
/* Screen implementation ends*/