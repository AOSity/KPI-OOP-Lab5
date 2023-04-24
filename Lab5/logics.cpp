#include "logics.h"
#include "GLFW/glfw3.h"
#include <typeinfo>

//#include <iostream>

/* Composite pattern */

/* Rectangle implementation */
void Rectangle::render()
{
	/* Render rectangle */
	glColor3f(red, green, blue);
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
void Rectangle::setPosition(double newXpos, double newYpos)
{
	xpos = newXpos;
	ypos = newYpos;
}
void Rectangle::getPosition(double* returnXpos, double* returnYpos)
{
	*returnXpos = xpos;
	*returnYpos = ypos;
}
Component* Rectangle::getCopy()
{
	Component* rectangleCopy = new Rectangle(xpos, ypos, width, height, red, green, blue);
	return rectangleCopy;
}
/* Rectangle implementation ends */

/* Circle implementation */
void Circle::render()
{
	/* Render circle*/
	glColor3f(red, green, blue);
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
void Circle::setPosition(double newXpos, double newYpos)
{
	xpos = newXpos;
	ypos = newYpos;
}
void Circle::getPosition(double* returnXpos, double* returnYpos)
{
	*returnXpos = xpos;
	*returnYpos = ypos;
}
Component* Circle::getCopy()
{
	Component* circleCopy = new Circle(xpos, ypos, radius, red, green, blue);
	return circleCopy;
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
	glColor3f(1, 1, 1);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin - 5, ymin - 5);
	glVertex2f(xmax + 5, ymin - 5);
	glVertex2f(xmax + 5, ymax + 5);
	glVertex2f(xmin - 5, ymax + 5);
	glEnd();
}
void Group::updateBorders()
{
	if (!isRoot)
	{
		xmin = 1930.f;
		xmax = -10.f;
		ymin = 1090.f;
		ymax = -10.f;
	}
	float cxmin, cxmax, cymin, cymax;
	for (Component* component : components)
	{
		if (typeid(*component) == typeid(Group))
		{
			((Group*)component)->updateBorders();
		}
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
}
void Group::add(Component* component)
{
	components.push_back(component);
	updateBorders();
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
		return foundComponent;
	}
	else
	{
		if (cursorX >= xmin && cursorX <= xmax && cursorY >= ymin && cursorY <= ymax)
		{
			return this;
		}
		else
		{
			return nullptr;
		}
	}
}
void Group::renderSelection()
{
	for (Component* component : components)
	{
		component->renderSelection();
	}

	glColor3f(1, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin - 5, ymin - 5);
	glVertex2f(xmax + 5, ymin - 5);
	glVertex2f(xmax + 5, ymax + 5);
	glVertex2f(xmin - 5, ymax + 5);
	glEnd();
}
void Group::eraseComponents()
{
	components.clear();
	if (!isRoot)
	{
		xmin = 1930.f;
		xmax = -10.f;
		ymin = 1090.f;
		ymax = -10.f;
	}
}
void Group::eraseSelected(set<Component*> selectedComponents, Group* group)
{
	for (int i = group->components.size() - 1; i >= 0; i--)
	{
		if (typeid(*(group->components[i])) == typeid(Group))
		{
			if (selectedComponents.find(group->components[i]) != selectedComponents.end()) // if component is in selectedComponent set
			{
				((Group*)group->components[i])->eraseComponents();
			}
			else
			{
				eraseSelected(selectedComponents, (Group*)group->components[i]);
			}
			if (((Group*)group->components[i])->components.empty())
			{
				group->components.erase(group->components.begin() + i);
				group->updateBorders();
			}
		}
		else if (selectedComponents.find(group->components[i]) != selectedComponents.end()) // if component is in selectedComponent set
		{
			group->components.erase(group->components.begin() + i);
			group->updateBorders();
		}
	}
	updateBorders();
}
void Group::setPosition(double newXpos, double newYpos)
{
	double groupXpos, groupYpos;
	getPosition(&groupXpos, &groupYpos);
	for (Component* component : components)
	{
		double componentXpos, componentYpos;
		component->getPosition(&componentXpos, &componentYpos);
		component->setPosition(componentXpos + newXpos - groupXpos, componentYpos + newYpos - groupYpos);
	}
	updateBorders();
}
void Group::getPosition(double* returnXpos, double* returnYpos)
{
	*returnXpos = xmin + (xmax - xmin) / 2.f;
	*returnYpos = ymin + (ymax - ymin) / 2.f;
}
Component* Group::getCopy()
{
	Group* groupCopy = new Group;
	if (isRoot)
	{
		groupCopy->isRoot = true;
		groupCopy->xmin = -10;
		groupCopy->xmax = 1930;
		groupCopy->ymin = -10;
		groupCopy->ymax = 1090;
	}
	for (Component* component : components)
	{
		groupCopy->add(component->getCopy());
	}
	return groupCopy;
}
/* Group implementation ends */

/* Screen implementation */
Screen::Screen()
{
	root = new Group;
	root->isRoot = true;
	root->xmin = -10;
	root->xmax = 1930;
	root->ymin = -10;
	root->ymax = 1090;
}
Screen::~Screen() 
{ 
	delete copiedComponent; 
	delete root; 
}
void Screen::render()
{
	root->render(); renderSelection();
}
void Screen::add(Component* component)
{
	if (selectedComponents.size() == 1)
	{
		for (Component* selected : selectedComponents)
		{
			if (typeid(*selected) == typeid(Group))
			{
				((Group*)selected)->add(component);
			}
			else
			{
				root->add(component);
			}
		}
	}
	else
	{
		root->add(component);
	}
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
		if (selected != root)
		{
			selectedComponents.insert(selected);
		}
	}
}
void Screen::selectAllGroup(Component* selected)
{
	if (typeid(*selected) == typeid(Group))
	{
		int i = 0;
		Component* component = selected->getChild(i);
		while (component != nullptr)
		{
			selectedComponents.insert(component);
			if (typeid(*component) == typeid(Group))
			{
				selectAllGroup(component);
			}
			i++;
			component = selected->getChild(i);
		}
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
	eraseSelection();
}
void Screen::eraseSelection()
{
	selectedComponents.clear();
}
void Screen::eraseSelected()
{
	root->eraseSelected(selectedComponents, root);
	eraseSelection();
}
void Screen::groupSelected()
{
	if (selectedComponents.size() >= 2)
	{
		Group* newGroup = new Group;
		for (Component* selected : selectedComponents)
		{
			newGroup->add(selected);
			root->remove(selected);
		}
		root->add(newGroup);
	}
	eraseSelection();
}
void Screen::moveToCursor(double cursorX, double cursorY)
{
	for (Component* selected : selectedComponents)
	{
		selected->setPosition(cursorX, cursorY);
	}
	root->updateBorders();
}
void Screen::copySelected()
{
	if (selectedComponents.size() == 1)
	{
		for (Component* selected : selectedComponents)
		{
			copiedComponent = selected->getCopy();
		}
	}
}
void Screen::pasteOnCursor(double cursorX, double cursorY)
{
	if (copiedComponent != nullptr)
	{
		copiedComponent->setPosition(cursorX, cursorY);

		if (selectedComponents.size() == 1)
		{
			for (Component* selected : selectedComponents)
			{
				if (typeid(*selected) == typeid(Group))
				{
					((Group*)selected)->add(copiedComponent->getCopy());
				}
				else
				{
					root->add(copiedComponent->getCopy());
				}
			}
		}
		else
		{
			root->add(copiedComponent->getCopy());
		}
	}
}
void Screen::backup()
{
	rootBackup.push_back((Group*)root->getCopy());
}
void Screen::undo()
{
	if (rootBackup.size() > 0)
	{
		root = rootBackup.back();
		rootBackup.pop_back();
		eraseSelection();
	}
}
/* Screen implementation ends*/