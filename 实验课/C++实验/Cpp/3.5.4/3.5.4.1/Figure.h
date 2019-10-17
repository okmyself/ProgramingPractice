#include <cstring>

class Shape {
private:
    std::string m_name;
public:
    Shape();
    Shape(std::string);
    float GetArea();
    void Set();
    void Show();
};

class Circle: Shape {
private:
    int m_x, m_y;
    int m_r;
public:
    Circle(int = 0);
    Circle(int, int, int = 0);
    void Set(int);
    void Set(int, int, int = 0);
    float GetArea();
    void Show();
};

class Rectangle: Shape {
private:
    int m_length, m_width;
public:
    Rectangle(int = 0, int = 0);
    void Set(int, int = 0);
    float GetArea();
    void Show();
};

class Triangle: Shape {
private:
    int m_bottom, m_height;
public:
    Triangle(int = 0, int = 0);
    void Set(int, int = 0);
    float GetArea();
    void Show();
};
