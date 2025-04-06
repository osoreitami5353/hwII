#ifndef EJERCICIOIII_H
#define EJERCICIOIII_H

#include <iostream>
#include <string>

class Number {
public:
    virtual Number* add(const Number& other) const = 0;
    virtual Number* subtract(const Number& other) const = 0;
    virtual Number* multiply(const Number& other) const = 0;
    virtual Number* divide(const Number& other) const = 0;
    virtual std::string toString() const = 0;
    virtual ~Number() {}
};

class Integer : public Number {
private:
    int value;
public:
    Integer(int v);
    Number* add(const Number& other) const override;
    Number* subtract(const Number& other) const override;
    Number* multiply(const Number& other) const override;
    Number* divide(const Number& other) const override;
    std::string toString() const override;
    int getValue() const;
};

class Real : public Number {
private:
    double value;
public:
    Real(double v);
    Number* add(const Number& other) const override;
    Number* subtract(const Number& other) const override;
    Number* multiply(const Number& other) const override;
    Number* divide(const Number& other) const override;
    std::string toString() const override;
    double getValue() const;
};

class Complex : public Number {
private:
    double real, imaginary;
public:
    Complex(double r, double i);
    Number* add(const Number& other) const override;
    Number* subtract(const Number& other) const override;
    Number* multiply(const Number& other) const override;
    Number* divide(const Number& other) const override;
    std::string toString() const override;
    double getReal() const;
    double getImaginary() const;
};

#endif