#ifndef _SHAPE_H_
#define _SHAPE_H_

class Circle {
protected:
    float radius;
public:
    Circle(float);
    virtual float area();
    virtual float volume();
};

class Sphere: Circle {
public:
    Sphere(float);
    float area();
    float volume();
};

class Column: Circle {
private:
    float height;
public:
    Column(float, float);
    float area();
    float volume();
};

#endif // Shape.h