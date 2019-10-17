#include "Shape.h"
#include <cstring>
#include <iostream>
#include <cmath>
// 形状
Shape::Shape(const char name[]): m_name(name) {}
void Shape::setName(std::string name) { m_name = name; }
std::string Shape::getName() const { return m_name; }
float Shape::getArea() const {}
void Shape::print() const {}
// 矩形
Rectangle::Rectangle(float length, float width): Shape("矩形") {
    if (length <= 0 || width <= 0)
        throw "长方体的长和宽必须大于0";
    m_length = length;
    m_width = width;
}
float Rectangle::getLength() const {
    return m_length;
}
void Rectangle::setLength(float length) {
    m_length = length;
}
float Rectangle::getWidth() const {
    return m_width;
}
void Rectangle::setWidth(float width) {
    m_width = width;
}
float Rectangle::getArea() const { return m_length * m_width; }
void Rectangle::print() const {
    std::cout << "形状: " << getName() << std::endl
              << "长: " << m_length << std::endl
              << "宽: " << m_width << std::endl
              << "面积: " << getArea() << std::endl;
}
// 三角形
Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3): Shape("三角形") {
    m_x1 = x1;  m_y1 = y1;
    m_x2 = x2;  m_y2 = y2;
    m_x3 = x3;  m_y3 = y3;
}
void Triangle::SetParameter(float x1, float y1, float x2, float y2, float x3, float y3) {
    m_x1 = x1;  m_y1 = y1;
    m_x2 = x2;  m_y2 = y2;
    m_x3 = x3;  m_y3 = y3;
}
float Triangle::getArea() const {
    float area;
    area =   m_x1 * m_y3 + m_x2 * m_y1 + m_x3 * m_y2
             - m_x1 * m_y2 - m_x2 * m_y3 - m_x3 * m_y1;
    area /= 2;
    if (area > 0)
        return area;
    else
        return -area;
}
void Triangle::print() const {
    std::cout << "形状: " << getName() << std::endl
              << "三个顶点坐标分别为: (" << m_x1 << ", " << m_y1 << ")、("
              << m_x2 << ", " << m_y2 << ")、("
              << m_x3 << ", " << m_y3 << ")" << std::endl
              << "面积: " << getArea() << std::endl;
}
// 圆形
Circle::Circle(float x, float y, float radius): Shape("圆形") {
    m_x = x;
    m_y = y;
    m_radius = radius;
}
void Circle::setX(float x) { m_x = x; }
float Circle::getX() const { return m_x; }
void Circle::setY(float y) { m_y = y; }
float Circle::getY() const { return m_y; }
float Circle::getRadius() const { return m_radius; }
void Circle::setRadius(float radius) { m_radius = radius; }
float Circle::getArea() const { return M_PI * m_radius * m_radius; }
void Circle::print() const {
    std::cout << "形状: " << getName() << std::endl
              << "半径: " << m_radius << std::endl
              << "面积: " << getArea() << std::endl;
}
