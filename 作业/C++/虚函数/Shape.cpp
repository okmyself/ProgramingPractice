#include "Shape.h"
#include <cmath>

Circle::Circle(float radius) {
    Circle::radius = radius;
}
float Circle::area() {
    return M_PI * radius * radius;
}
float Circle::volume() { return 0; }

Sphere::Sphere(float radius) : Circle(radius) {}
float Sphere::area() {
    return static_cast<float>(4 * M_PI * radius * radius);
}
float Sphere::volume() {
    return static_cast<float>(4 / 3.0 * M_PI * radius * radius * radius);
}

Column::Column(float radius, float height) : Circle(radius) {
    Column::height = height;
}
float Column::area() {
    return static_cast<float>(2 * M_PI * radius * (radius + height));
}
float Column::volume() {
    return static_cast<float>(M_PI * radius * radius * height);
}