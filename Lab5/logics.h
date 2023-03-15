#pragma once

#include <vector>

/* Composite */
class Component
{
public:
    virtual ~Component() {}
    virtual void operation() = 0;
    virtual void add(Component* component) {}
    virtual void remove(Component* component) {}
    virtual Component* getChild(int index) { return nullptr; }
};
class Rectangle : public Component {
public:
    double xpos, ypos;
    Rectangle(double x, double y) : xpos(x), ypos(y) {};
    void operation() override;
};
class Circle : public Component {
public:
    double xpos, ypos;
    Circle(double x, double y) : xpos(x), ypos(y) {};
    void operation() override;
};
class Group : public Component {
private:
    std::vector<Component*> components;
public:
    double xpos, ypos;
    Group(double x, double y) : xpos(x), ypos(y) {};
    ~Group();
    void operation() override;
    void add(Component* component) override;
    void remove(Component* component) override;
    Component* getChild(int index) override;
};
/* */