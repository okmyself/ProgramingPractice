#include <iostream>
#include <cmath>
#include "Figure.h"

Shape::Shape(): m_name("shape") {}
Shape::Shape(std::string name): m_name(name) {}
float Shape::GetArea() {}
void Shape::Set() {}
void Shape::Show() {}

Circle::Circle(int r): Shape("circle") {
    if (r < 0) {
        std::cout << "半径输入错误" << std::endl;
        r = 0;
    }
    m_x = 0;
    m_y = 0;
    m_r = r;
}
Circle::Circle(int x, int y, int r): Shape("circle") {
    if (r < 0) {
        std::cout << "半径输入错误" << std::endl;
        r = 0;
    }
    m_x = x;
    m_y = y;
    m_r = r;
}
void Circle::Set(int r) {
    if (r < 0) {
        std::cout << "半径输入错误" << std::endl;
        r = 0;
    }
    m_r = r;
}
void Circle::Set(int x, int y, int r) {
    if (r < 0) {
        std::cout << "半径输入错误" << std::endl;
        r = 0;
    }
    m_x = x;
    m_y = y;
    m_r = r;
}
float Circle::GetArea() {
    return M_PI * m_r * m_r;
}
void Circle::Show() {
    std::cout << "圆心坐标: (" << m_x << ", " << m_y << ')' << std::endl
              << "直径: " << 2 * m_r << std::endl
              << "周长: " << 2 * M_PI * m_r << std::endl
              << "面积: " << GetArea() << std::endl;
}

Rectangle::Rectangle(int length, int width): Shape("rectangle") {
    if (length < 0) {
        std::cout << "长输入错误" << std::endl;
        length = 0;
    }
    if (width < 0) {
        std::cout << "宽输入错误" << std::endl;
        width = 0;
    }
    m_length = length;
    m_width = width;
}
void Rectangle::Set(int length, int width) {
    if (length < 0) {
        std::cout << "长输入错误" << std::endl;
        length = 0;
    }
    if (width < 0) {
        std::cout << "宽输入错误" << std::endl;
        width = 0;
    }
    m_length = length;
    m_width = width;
}
float Rectangle::GetArea() {
    return m_length * m_width;
}
void Rectangle::Show() {
    std::cout << "长: " << m_length << std::endl
              << "宽: " << m_width << std::endl
              << "周长: " << 2 * (m_length + m_width) << std::endl
              << "面积: " << GetArea() << std::endl;
}

Triangle::Triangle(int bottom, int height): Shape("triangle") {
    if (bottom < 0) {
        std::cout << "底输入错误" << std::endl;
        bottom = 0;
    }
    if (height < 0) {
        std::cout << "高输入错误" << std::endl;
        height = 0;
    }
    m_bottom = bottom;
    m_height = height;
}
void Triangle::Set(int bottom, int height) {
    if (bottom < 0) {
        std::cout << "底输入错误" << std::endl;
        bottom = 0;
    }
    if (height < 0) {
        std::cout << "高输入错误" << std::endl;
        height = 0;
    }
    m_bottom = bottom;
    m_height = height;
}
float Triangle::GetArea() {
    return m_bottom * m_height * 0.5;
}
void Triangle::Show() {
    std::cout << "底: " << m_bottom << std::endl
              << "高: " << m_height << std::endl
              << "面积: " << GetArea() << std::endl;
}
