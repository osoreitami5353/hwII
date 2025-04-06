#include "EjercicioIII.hpp"
#include <sstream>

// ===================== ENTERO =====================

Integer::Integer(int v) : value(v) {}

// Función para sumar un entero con otro número (Entero, Real o Complejo)
Number* Integer::add(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Integer(value + i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Real(value + r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(value + c->getReal(), c->getImaginary());

    return nullptr;

}

// Función para restar un entero con otro número
Number* Integer::subtract(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Integer(value - i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Real(value - r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(value - c->getReal(), -c->getImaginary());

    return nullptr;

}

// Función para multiplicar un entero con otro número
Number* Integer::multiply(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Integer(value * i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Real(value * r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(value * c->getReal(), value * c->getImaginary());

    return nullptr;

}

// Función para dividir un entero con otro número
Number* Integer::divide(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i && i->getValue() != 0) return new Real((double)value / i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r && r->getValue() != 0.0) return new Real(value / r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    // División de un número entero/real por complejo:
    // (a) / (c + di) = [a(c - di)] / (c² + d²)
    if (c && (c->getReal() != 0 || c->getImaginary() != 0)) {
        double denom = c->getReal()*c->getReal() + c->getImaginary()*c->getImaginary();
        double realPart = value * c->getReal() / denom;
        double imagPart = -value * c->getImaginary() / denom;
        return new Complex(realPart, imagPart);
    }

    return nullptr;

}

// Función que devuelve el valor entero como string
/*
        Busqué información referida a la función std::to_string() de C++ y encontré que lo mejor en este caso era usar std::to_string() para convertir el entero a string, pero sé que aún no lo vimos en clase, al igual que "std::ostringstream", y a pesar de esto decidí usarlos ya que ya he trabajado otras veces con ellos y me parecen más simples de usar que la función "sprintf" de C, pero aún así añadiré aquí el funcionamiento tanto de "std::to_string()" como de "std::ostringstream" para que quede claro el funcionamiento de ambos, y cómo podría ser una solución con "sprintf":

        std::to_string: Es una función de la biblioteca estándar de C++ (<string>) que convierte valores numéricos a texto (std::string). Internamente, toma un número (como un int, float, double, etc.) y lo transforma en una cadena de texto que representa su valor. Uso std::to_string cuando deseo convertir un solo número a texto de forma directa y rápida, pero tiene una limitación que es que solo convierte tipos numéricos uno a uno, es decir, no se puede usar para combinar varios valores fácilmente.

        std::ostringstream: Es un tipo de stream de salida (como std::cout) que escribe en una variable string en lugar de imprimir por pantalla. Funciona igual que std::cout, pero en vez de mostrar por consola, guarda el texto internamente en un std::string que podés recuperar después. Uso std::ostringstream cuando quiero construir un string más complejo, por ejemplo, mezclando números, texto, signos o valores en una sola frase, por lo que no tiene la limitación de std::to_string permitiendome armar frases completas, como cuando deseo mostrar un número complejo con "3+4i", algo que to_string solo no puede hacer.

        Ejemplo con sprintf:
            char buffer[50];
            sprintf(buffer, "%.2f%+.2fi", real, imaginary);
            std::string result = buffer;
        
        Como se puede ver, permite realizar lo mismo, solo que con la limitación de tener que suponer un máximo de caracteres a usar (más bien en el caso de mi código, máximo de caracteres que el usuario desee usar, lo que me es imposible de adivinar), y además no es tan simple de usar como las funciones de C++.

    */
std::string Integer::toString() const {
    return std::to_string(value);

}

// Función para obtener el valor entero
int Integer::getValue() const {
    return value;

}

// ===================== REAL =====================

Real::Real(double v) : value(v) {}

// Función para sumar un real con otro número
Number* Real::add(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Real(value + i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Real(value + r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(value + c->getReal(), c->getImaginary());

    return nullptr;

}

// Función para restar un real con otro número
Number* Real::subtract(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Real(value - i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Real(value - r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(value - c->getReal(), -c->getImaginary());

    return nullptr;

}

// Función para multiplicar un real con otro número
Number* Real::multiply(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Real(value * i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Real(value * r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(value * c->getReal(), value * c->getImaginary());

    return nullptr;

}

// Función para dividir un real con otro número
Number* Real::divide(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i && i->getValue() != 0) return new Real(value / i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r && r->getValue() != 0.0) return new Real(value / r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    // División de un número entero/real por complejo:
    // (a) / (c + di) = [a(c - di)] / (c² + d²)
    if (c && (c->getReal() != 0 || c->getImaginary() != 0)) {
        double denom = c->getReal()*c->getReal() + c->getImaginary()*c->getImaginary();
        double realPart = value * c->getReal() / denom;
        double imagPart = -value * c->getImaginary() / denom;

        return new Complex(realPart, imagPart);

    }

    return nullptr;
}

// Función que devuelve el valor real como string
std::string Real::toString() const {
    std::ostringstream oss;
    oss << value;
    return oss.str();

}

// Función para obtener el valor real
double Real::getValue() const {
    return value;

}

// ===================== COMPLEJOS =====================

Complex::Complex(double r, double i) : real(r), imaginary(i) {}

// Función para sumar un complejo con otro número
Number* Complex::add(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Complex(real + i->getValue(), imaginary);

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Complex(real + r->getValue(), imaginary);

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(real + c->getReal(), imaginary + c->getImaginary());

    return nullptr;

}

// Función para restar un complejo con otro número
Number* Complex::subtract(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Complex(real - i->getValue(), imaginary);

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Complex(real - r->getValue(), imaginary);

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) return new Complex(real - c->getReal(), imaginary - c->getImaginary());

    return nullptr;

}

// Función para multiplicar un complejo con otro número
Number* Complex::multiply(const Number& other) const {
    // Si el segundo valor es de tipo entero:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i) return new Complex(real * i->getValue(), imaginary * i->getValue());

    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r) return new Complex(real * r->getValue(), imaginary * r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    if (c) {
        // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
        double a = real, b = imaginary;
        double cR = c->getReal(), cI = c->getImaginary();
        double r = a * cR - b * cI;
        double i = a * cI + b * cR;
        return new Complex(r, i);

    }

    return nullptr;

}

// Función para dividir un complejo con otro número
Number* Complex::divide(const Number& other) const {
    // Si el segundo valor es de tipo complejo:
    const Integer* i = dynamic_cast<const Integer*>(&other);
    if (i && i->getValue() != 0)
        return new Complex(real / i->getValue(), imaginary / i->getValue());
    
    // Si el segundo valor es de tipo real:
    const Real* r = dynamic_cast<const Real*>(&other);
    if (r && r->getValue() != 0.0)
        return new Complex(real / r->getValue(), imaginary / r->getValue());

    // Si el segundo valor es de tipo complejo:
    const Complex* c = dynamic_cast<const Complex*>(&other);
    // División de complejos:
    // (a + bi) / (c + di) = [(ac + bd) + (bc - ad)i] / (c² + d²)
    if (c && (c->getReal() != 0 || c->getImaginary() != 0)) {
        double a = real, b = imaginary;
        double cR = c->getReal(), cI = c->getImaginary();
        double denom = cR*cR + cI*cI;
        double rPart = (a * cR + b * cI) / denom;
        double iPart = (b * cR - a * cI) / denom;

        return new Complex(rPart, iPart);
        
    }

    return nullptr;
}

// Función que devuelve el número complejo como string (formato a+bi)
std::string Complex::toString() const {
    std::ostringstream oss;
    oss << real;
    if (imaginary >= 0) oss << "+";
    oss << imaginary << "i";

    return oss.str();

}


// Función para obtener la parte real
double Complex::getReal() const {
    return real;

}

// Función para obtener la parte imaginaria
double Complex::getImaginary() const {
    return imaginary;

}