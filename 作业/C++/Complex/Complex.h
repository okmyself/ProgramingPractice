#ifndef _COMPLEX_H_
#define _COMPLEX_H_

class Complex {
private:
    double real;    // real part
    double imaginary;   // imaginary part
public:
    Complex(double = 0, double = 0);
    Complex(const Complex&);    // copy constructor
    //getter, setter
    void setRealPart(double);
    double getRealPart() const;
    void setImaginaryPart(double);
    double getImaginaryPart() const;
    Complex Add(const Complex&) const;
    Complex Sub(const Complex&) const;
    Complex Mul(const Complex&) const;
    Complex Div(const Complex&) const;
    inline double Mold() const;
    //operator overloading
    inline bool operator== (const Complex&) const;
    inline bool operator!= (const Complex&) const;
    inline Complex operator+ (const Complex&);
    inline Complex operator- (const Complex&);
    inline Complex operator* (const Complex&);
    inline Complex operator/ (const Complex&);
    Complex& operator+= (const Complex&);
    Complex& operator-= (const Complex&);
    Complex& operator*= (const Complex&);
    Complex& operator/= (const Complex&);
};

#endif