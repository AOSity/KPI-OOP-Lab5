#pragma once

#include <vector>
#include <set>

/* Composite pattern */
/* Component -> Rectangle, Circle, Group of them */

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
	Group() : xmin(1921.f), xmax(-1.f), ymin(1081.f), ymax(-1.f) {};
	~Group();
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
	void renderSelection() override {}
	Component* onCursor(double cursorX, double cursorY) override;
	void add(Component* component) override;
	void remove(Component* component) override;
	Component* getChild(int index) override;
	void eraseComponents();
};
/* Composite pattern ends */

/* Facede? Screen to operate with root */
class Screen
{
private:
	Group* root;
	std::set<Component*> selectedComponents;
public:
	Screen() { root = new Group; }
	~Screen() { /* delete root brings access violation */ }
	void render();
	void add(Component* component);
	void remove(Component* component);
	Component* findOnCursor(double cursorX, double cursorY);
	void selectOnCursor(double cursorX, double cursorY);
	void renderSelection();
	void eraseComponents();
	void eraseSelection();
};
/* Facade? ends */