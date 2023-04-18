#pragma once

#include <vector>
#include <set>

using namespace std;

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
	float red, green, blue;
	Rectangle(float x, float y, float w, float h, float r = 0, float g = 0.5, float b = 1) : xpos(x), ypos(y), width(w), height(h), red(r), green(g), blue(b) {}
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
	void renderSelection() override;
	Component* onCursor(double cursorX, double cursorY) override;
};
class Circle : public Component {
public:
	float xpos, ypos, radius;
	float red, green, blue;
	Circle(float x, float y, float rad, float r = 1, float g = 1, float b = 0) : xpos(x), ypos(y), radius(rad), red(r), green(g), blue(b) {}
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
	void renderSelection() override;
	Component* onCursor(double cursorX, double cursorY) override;
};
class Group : public Component {
private:
	vector<Component*> components;
public:
	double xmin, xmax, ymin, ymax;
	Group() : xmin(1930.f), xmax(-10.f), ymin(1090.f), ymax(-10.f) {};
	~Group();
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
	void renderSelection() override;
	Component* onCursor(double cursorX, double cursorY) override;
	void add(Component* component) override;
	void remove(Component* component) override;
	Component* getChild(int index) override;
	void eraseComponents();
	void updateBorders();
	void eraseSelected(set<Component*> selectedComponents, Group* group);
};
/* Composite pattern ends */

/* Facede? Screen to operate with root */
class Screen
{
private:
	Group* root;
	set<Component*> selectedComponents;
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
	void eraseSelected() {root->eraseSelected(selectedComponents, root); }
	void groupSelected()
	{
		Group* newGroup = new Group;
		for (Component* selected : selectedComponents)
		{
			newGroup->add(move(selected));
		}
		root->add(newGroup);
		//eraseSelected();
		eraseSelection();
	}
private:
	void selectAllGroup(Component* selected);
};
/* Facade? ends */