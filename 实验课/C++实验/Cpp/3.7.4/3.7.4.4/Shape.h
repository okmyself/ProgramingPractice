#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <string>

class Shape {
private:
    std::string m_name;
public:
    Shape(const char[] = "形状");
    void setName(std::string);
    std::string getName() const;

    virtual float getArea() const;
    virtual void print() const;
};

class Rectangle: public Shape {
private:
    float m_length, m_width;
public:
    Rectangle(float, float);
    float getLength() const;
    void setLength(float length);
    float getWidth() const;
    void setWidth(float width);
    float getArea() const;
    void print() const;
};

class Triangle: public Shape {
private:
    float m_x1, m_y1, m_x2, m_y2, m_x3, m_y3;   //三角形三边
public:
    Triangle(float, float, float, float, float, float);
    void SetParameter(float, float, float, float, float, float);
    float getArea() const;
    void print() const;
};

class Circle: public Shape {
private:
    float m_x, m_y, m_radius;
public:
    Circle(float, float, float);
    void setX(float);
    float getX() const;
    void setY(float);
    float getY() const;
    float getRadius() const;
    void setRadius(float radius);
    float getArea() const;
    void print() const;
};

#endif /* Shape.h */

