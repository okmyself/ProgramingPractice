#ifndef _SHAPE_H_
#define _SHAPE_H_

class Shape {
protected:
    char name[10];
    float area; // 面积
public:
    const char *getName() const;
    float getArea() const;
    void setArea(float);
    Shape(float = 0, const char[] = "形状");

    void print() const;
};

class TwoDimShape: public Shape {
protected:
    float perimeter;    // 周长
public:
    TwoDimShape(float = 0, float = 0, const char[] = "二维形状");
    float getPerimeter() const;
    void setPerimeter(float);
    void print() const;
};

class ThreeDimShape: public Shape {
protected:
    float volume;   //体积
public:
    ThreeDimShape(float = 0, float = 0, const char[] = "三维形状");
    float getVolume() const;
    void setVolume(float volume);
    void print() const;
};

class Rectangle: public TwoDimShape {
private:
    float length, width;
public:
    Rectangle(float, float);
    float getLength() const;
    void setLength(float length);
    float getWidth() const;
    void setWidth(float width);
    void print() const;
};

class Triangle: public TwoDimShape {
private:
    float a, b, c;  //三角形三边
public:
    Triangle(float, float, float);
    void SetSide(float, float, float);
    void print() const;
};

class Circle: public TwoDimShape {
private:
    float radius;
public:
    Circle(float);
    float getRadius() const;
    void setRadius(float radius);
    void print() const;
};

class Cuboid: public ThreeDimShape {
private:
    float length, width, height;
public:
    Cuboid(float, float, float);
    float getLength() const;
    void setLength(float length);
    float getWidth() const;
    void setWidth(float width);
    float getHeight() const;
    void setHeight(float height);
    void print() const;
};

class Sphere: public ThreeDimShape {
private:
    float radius;
public:
    Sphere(float);
    float getRadius() const;
    void setRadius(float radius);
    void print() const;
};

#endif /* Shape.h */