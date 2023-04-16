#pragma once

#include <vector>
#include <set>

/* Composite */
class Component
{
public:
	virtual ~Component() {}
	virtual void borders(float* xmin, float* xmax, float* ymin, float* ymax) = 0;
	virtual void render() = 0;
	virtual void renderSelection() {}
	virtual void add(Component* component) {}
	virtual void remove(Component* component) {}
	virtual Component* onCursor(double cursorX, double cursorY) { return nullptr; }
	virtual Component* getChild(int index) { return nullptr; }
};
class Rectangle : public Component {
public:
	float xpos, ypos, width, height;
	Rectangle(float x, float y, float w, float h) : xpos(x), ypos(y), width(w), height(h) {}
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
	void renderSelection() override;
	Component* onCursor(double cursorX, double cursorY) override;
};
class Circle : public Component {
public:
	float xpos, ypos, radius;
	Circle(float x, float y, float r) : xpos(x), ypos(y), radius(r) {}
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
	void renderSelection() override;
	Component* onCursor(double cursorX, double cursorY) override;
};
class Group : public Component {
private:
	std::vector<Component*> components;
public:
	double xmin, xmax, ymin, ymax;
	Group() : xmin(1920.f), xmax(0.f), ymin(1080.f), ymax(0.f) {};
	~Group();
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
	void renderSelection() override {}
	Component* onCursor(double cursorX, double cursorY) override;
	void add(Component* component) override;
	void remove(Component* component) override;
	Component* getChild(int index) override;
};
/* */

#include <iostream>

class Screen
{
public:
	Group* root;
	Screen() { root = new Group; }
	~Screen() { /* ? */ }
	void render() { root->render(); renderSelection(); }
	void add(Component* component) { root->add(component); }
	void remove(Component* component) { root->remove(component); }
	Component* findOnCursor(double cursorX, double cursorY) { return root->onCursor(cursorX, cursorY); }

	std::set<Component*> selectedComponents;
	void selectOnCursor(double cursorX, double cursorY) 
	{ 
		Component* selected;
		if ((selected = findOnCursor(cursorX, cursorY)) != nullptr)
		{
			selectedComponents.insert(selected);
		}
	}
	void renderSelection()
	{
		for (Component* selected : selectedComponents)
		{
			selected->renderSelection();
		}
	}
};