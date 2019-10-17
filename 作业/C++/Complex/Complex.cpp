#include "Complex.h"
#include <math.h>

Complex::Complex(double real_part, double imaginary_part)
                : real(real_part)
                , imaginary(imaginary_part)
{}
Complex::Complex(const Complex& a)
                : real(a.real)
                , imaginary(a.imaginary)
{}
void Complex::setRealPart(double r) { real = r; }
double Complex::getRealPart() const { return real; }
void Complex::setImaginaryPart(double i) { imaginary = i; }
double Complex::getImaginaryPart() const { return imaginary; }
Complex Complex::Add(const Complex& a) const {
    Complex b(a);
    b.real += real;
    b.imaginary += imaginary;
    return b;
}
Complex Complex::Sub(const Complex& a) const {
    Complex b;
    b.real = real - a.real;
    b.imaginary = imaginary - a.imaginary;
    return b;
}
Complex Complex::Mul(const Complex& a) const {
    Complex b;
    b.real = real * a.real - imaginary * a.imaginary;
    b.imaginary = real * a.imaginary + imaginary * a.real;
    return b;
}
Complex Complex::Div(const Complex& a) const {
    int denominator = a.real * a.real + a.imaginary * a.imaginary;
    // if(denominator == 0)
    //     throw "mold of 'a' cannot be zero";
    Complex b;
    b.real = (real * a.real + imaginary * a.imaginary) / denominator;
    b.imaginary = (imaginary * a.real - real * a.imaginary) / denominator;
    return b;
}
double Complex::Mold() const {
    return sqrt(real * real + imaginary * imaginary);
}
bool Complex::operator== (const Complex& a) const {
    return real == a.real && imaginary == a.imaginary;
}
bool Complex::operator!= (const Complex& a) const {
    return real != a.real || imaginary != a.imaginary;
}
Complex Complex::operator+ (const Complex& a) { return Add(a); }
Complex Complex::operator- (const Complex& a) { return Sub(a); }
Complex Complex::operator* (const Complex& a) { return Mul(a); }
Complex Complex::operator/ (const Complex& a) { return Div(a); }
Complex& Complex::operator+= (const Complex& a) {
    Complex temp = this->Add(a);
    real = temp.real;
    imaginary = temp.imaginary;
    return *this;
}
Complex& Complex::operator-= (const Complex& a) {
    Complex temp = this->Sub(a);
    real = temp.real;
    imaginary = temp.imaginary;
    return *this;
}
Complex& Complex::operator*= (const Complex& a) {
    Complex temp = this->Mul(a);
    real = temp.real;
    imaginary = temp.imaginary;
    return *this;
}
Complex& Complex::operator/= (const Complex& a) {
    Complex temp = this->Div(a);
    real = temp.real;
    imaginary = temp.imaginary;
    return *this;
}