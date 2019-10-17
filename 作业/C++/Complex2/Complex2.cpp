#include "Complex2.h"
#include <math.h>

Complex::Complex(float real, float imag)
    : m_real(real)
    , m_imag(imag)
{}
Complex::Complex(float real)
    : m_real(real)
    , m_imag(0)
{}
Complex::Complex(const Complex& right)
    : m_real(right.m_real)
    , m_imag(right.m_imag)
{}
void Complex::setReal(float real) { m_real = real; }
float Complex::getReal() const { return m_real; }
void Complex::setImag(float imag) { m_imag = imag; }
float Complex::getImag() const { return m_imag; }
Complex::operator bool() const {
    return m_real != 0 || m_imag != 0;
}
float Complex::operator() () const {
    return sqrt(m_real * m_real + m_imag * m_imag);
}
bool Complex::operator== (const Complex& right) const {
    return m_real == right.m_real && m_imag == right.m_imag;
}
bool Complex::operator!= (const Complex& right) const {
    return m_real != right.m_real || m_imag != right.m_imag;
}
Complex Complex::operator+ (const Complex& right) const {
    Complex left(right);
    left.m_real += m_real;
    left.m_imag += m_imag;
    return left;
}
Complex Complex::operator- (const Complex& right) const {
    Complex left;
    left.m_real = m_real - right.m_real;
    left.m_imag = m_imag - right.m_imag;
    return left;
}
Complex Complex::operator* (const Complex& right) const {
    Complex left;
    left.m_real = m_real * right.m_real - m_imag * right.m_imag;
    left.m_imag = m_real * right.m_imag + m_imag * right.m_real;
    return left;
}
Complex Complex::operator/ (const Complex& right) const {
    float denominator = right.m_real * right.m_real + right.m_imag * right.m_imag;
    if(denominator == 0)
        throw "mold of 'right' cannot be zero";
    Complex left;
    left.m_real = (m_real * right.m_real + m_imag * right.m_imag) / denominator;
    left.m_imag = (m_imag * right.m_real - m_real * right.m_imag) / denominator;
    return left;
}
Complex Complex::operator+ () const {
    return Complex(*this);
}
Complex Complex::operator- () const {
    return Complex(-this->m_real, -this->m_imag);
}
Complex& Complex::operator+= (const Complex& right) {
    Complex left = *this + right;
    m_real = left.m_real;
    m_imag = left.m_imag;
    return *this;
}
Complex& Complex::operator-= (const Complex& right) {
    Complex left = *this - right;
    m_real = left.m_real;
    m_imag = left.m_imag;
    return *this;
}
Complex& Complex::operator*= (const Complex& right) {
    Complex left = *this * right;
    m_real = left.m_real;
    m_imag = left.m_imag;
    return *this;
}
Complex& Complex::operator/= (const Complex& right) {
    Complex left = *this / right;
    m_real = left.m_real;
    m_imag = left.m_imag;
    return *this;
}
std::ostream& operator<< (std::ostream &os, const Complex &c) {
    if (c.m_real != 0) {
        os << c.m_real;
        if (c.m_imag > 0) os << '+';
    }
    if (c.m_imag != 0) {
        if (c.m_imag == 1) ;
        else if (c.m_imag == -1) os << '-';
        else os << c.m_imag;
        os << 'i';
    }
    return os;
}
Complex operator+ (float left, const Complex &right) {
    Complex temp(right);
    temp.m_real += left;
    return temp;
}
Complex operator- (float left, const Complex &right) {
    Complex temp(right);
    temp.m_real -= left;
    temp.m_imag = -temp.m_imag;
    return temp;
}
Complex operator* (float left, const Complex &right) {
    Complex temp(right);
    temp.m_real *= left;
    temp.m_imag *= left;
    return temp;
}
Complex operator/ (float left, const Complex &right) {
//    float denominator = right.m_real * right.m_real + right.m_imag * right.m_imag;
//    if(denominator == 0)
//        throw "mold of 'right' cannot be zero";
//    Complex temp(right);
//    temp.m_real /= (denominator / left);
//    temp.m_imag /= (-denominator / left);
//    return temp;
    return Complex(left) / right;
}