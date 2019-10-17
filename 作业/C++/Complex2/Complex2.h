#ifndef _COMPLEX2_H_
#define _COMPLEX2_H_
#include <iostream>

class Complex {
private:
    float m_real;   // real part
    float m_imag;   // imaginary part
public:
    // constructors
    Complex(float, float);
    Complex(float = 0);         // conversion constructor
    Complex(const Complex&);    // copy constructor
    // getters, setters
    void setReal(float);
    float getReal() const;
    void setImag(float);
    float getImag() const;
    // operator overloading
    explicit operator bool() const; // safe bool, C++11 support is required
    float operator() () const;  // get mold
    bool operator== (const Complex&) const;
    bool operator!= (const Complex&) const;
    Complex operator+ (const Complex&) const;   // addition
    Complex operator- (const Complex&) const;   // substract
    Complex operator* (const Complex&) const;   // multiplication
    Complex operator/ (const Complex&) const;   // division
    Complex operator+ () const; // plus
    Complex operator- () const; // minus
    Complex& operator+= (const Complex&);
    Complex& operator-= (const Complex&);
    Complex& operator*= (const Complex&);
    Complex& operator/= (const Complex&);
    // friend function
    friend std::ostream& operator<< (std::ostream&, const Complex&);    // output
    friend Complex operator+ (float, const Complex&);
    friend Complex operator- (float, const Complex&);
    friend Complex operator* (float, const Complex&);
    friend Complex operator/ (float, const Complex&);
};

#endif /* _COMPLEX2_H_ */