#pragma once

#include <vector>

/* Composite */
class Component
{
public:
	virtual ~Component() {}
	virtual void borders(float* xmin, float* xmax, float* ymin, float* ymax) = 0;
	virtual void render() = 0;
	virtual void add(Component* component) {}
	virtual void remove(Component* component) {}
	virtual Component* getChild(int index) { return nullptr; }
};
class Rectangle : public Component {
public:
	float xpos, ypos, width, height;

	Rectangle(float x, float y, float w, float h) : xpos(x), ypos(y), width(w), height(h) {}
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
};
class Circle : public Component {
public:
	float xpos, ypos, radius;
	Circle(float x, float y, float r) : xpos(x), ypos(y), radius(r) {}
	void borders(float* xmin, float* xmax, float* ymin, float* ymax) override;
	void render() override;
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
	void add(Component* component) override;
	void remove(Component* component) override;
	Component* getChild(int index) override;
};
/* */