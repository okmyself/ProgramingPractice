#include "Shape.h"
#include <cstring>
#include <iostream>
#include <cmath>
// 形状
Shape::Shape(float area, const char name[]) {
    this->area = area;
    strcpy(this->name, name);
}
void Shape::print() const {
    std::cout << "形状名称：" << name << std::endl
              << "面积：" << area << std::endl;
}
const char* Shape::getName() const {
    return name;
}
float Shape::getArea() const {
    return area;
}
void Shape::setArea(float area) {
    Shape::area = area;
}
// 二维形状
TwoDimShape::TwoDimShape(float perimeter, float area, const char name[]): Shape(area, name) {
    this->perimeter = perimeter;
}
float TwoDimShape::getPerimeter() const {
    return perimeter;
}
void TwoDimShape::setPerimeter(float perimeter) {
    TwoDimShape::perimeter = perimeter;
}
void TwoDimShape::print() const {
    Shape::print();
    std::cout << "周长：" << perimeter << std::endl;
}
// 三维形状
ThreeDimShape::ThreeDimShape(float volume, float area, const char name[]): Shape(area, name) {
    this->volume = volume;
}
float ThreeDimShape::getVolume() const {
    return volume;
}
void ThreeDimShape::setVolume(float volume) {
    ThreeDimShape::volume = volume;
}
void ThreeDimShape::print() const
{
    Shape::print();
    std::cout << "体积：" << volume << std::endl;
}
// 矩形
Rectangle::Rectangle(float length, float width)
                    : TwoDimShape(
                        2 * (length + width),
                        length * width, "矩形") {
    if (length <= 0 || width <= 0)
        throw "长方体的长和宽必须大于0";
    this->length = length;
    this->width = width;
}
float Rectangle::getLength() const {
    return length;
}
void Rectangle::setLength(float length) {
    Rectangle::length = length;
}
float Rectangle::getWidth() const {
    return width;
}
void Rectangle::setWidth(float width) {
    Rectangle::width = width;
}
void Rectangle::print() const {
    TwoDimShape::print();
    std::cout << "长：" << length << std::endl
              << "宽：" << width << std::endl;
}
// 三角形
Triangle::Triangle(float a, float b, float c)
                    : TwoDimShape(
                        a + b + c,
                        0, "三角形") {
    if (a + b <= c || a + c <= b || b + c <= a)
        throw "a, b, c不能构成三角形";
    float p = (a + b + c) / 2;
    TwoDimShape::area = sqrt(p * (p - a) * (p - b) * (p - c));
    this->a = a;
    this->b = b;
    this->c = c;
}
void Triangle::SetSide(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}
void Triangle::print() const {
    TwoDimShape::print();
    std::cout << "三边长分别为：" << a << "、" << b << "、" << c << std::endl;
}
// 圆形
Circle::Circle(float radius)
                : TwoDimShape(
                    static_cast<float>(2 * M_PI * radius),
                    static_cast<float>(M_PI * radius * radius), "圆形") {
    this->radius = radius;
}
float Circle::getRadius() const {
    return radius;
}
void Circle::setRadius(float radius) {
    Circle::radius = radius;
}
void Circle::print() const {
    TwoDimShape::print();
    std::cout << "半径：" << radius << std::endl;
}
// 长方体
Cuboid::Cuboid(float length, float width, float height)
                :ThreeDimShape(
                    length * width * height,
                    2 * (length * width + length * height + width * height), "长方体"){
    this->length = length;
    this->width = width;
    this->height = height;
}
float Cuboid::getLength() const {
    return length;
}
void Cuboid::setLength(float length) {
    Cuboid::length = length;
}
float Cuboid::getWidth() const {
    return width;
}
void Cuboid::setWidth(float width) {
    Cuboid::width = width;
}
float Cuboid::getHeight() const {
    return height;
}
void Cuboid::setHeight(float height) {
    Cuboid::height = height;
}
void Cuboid::print() const {
    ThreeDimShape::print();
    std::cout << "长：" << length << std::endl
              << "宽：" << width << std::endl
              << "高：" << height << std::endl;
}
// 球体
Sphere::Sphere(float radius)
                : ThreeDimShape(
                    static_cast<float>(4 / 3.0 * M_PI * radius * radius * radius),
                    static_cast<float>(4 * M_PI * radius * radius), "球体") {
    this->radius = radius;
}
float Sphere::getRadius() const {
    return radius;
}
void Sphere::setRadius(float radius) {
    Sphere::radius = radius;
}
void Sphere::print() const {
    ThreeDimShape::print();
    std::cout << "半径：" << radius << std::endl;
}