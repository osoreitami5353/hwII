#include <iostream>
#include "EjercicioIII.hpp"

Number* createNumberFromInput(int numIndex) {
    int type;
    std::cout << "====================================================================" << std::endl;
    std::cout << "\nSelecciona el tipo del valor " << numIndex << "°:\n";
    std::cout << "1. Entero\n2. Real\n3. Complejo\n\n> ";
    std::cin >> type;

    if (type == 1) {
        int val;
        std::cout << "\nIngrese un número entero: ";
        std::cin >> val;
        return new Integer(val);
    }
    else if (type == 2) {
        double val;
        std::cout << "\nIngrese un número real: ";
        std::cin >> val;
        return new Real(val);
    }
    else if (type == 3) {
        double r, i;
        std::cout << "\nIngrese la parte real: ";
        std::cin >> r;
        std::cout << "\nIngrese la parte imaginaria: ";
        std::cin >> i;
        return new Complex(r, i);
    }
    else {
        std::cout << "\nTipo inválido. Se usará 0 como Integer por defecto.\n";
        return new Integer(0);
    }
}

int main() {
    std::cout << "=== Operaciones entre diferentes tipos de números ===\n";

    Number* n1 = createNumberFromInput(1);
    Number* n2 = createNumberFromInput(2);

    Number* sum = n1->add(*n2);
    Number* sub = n1->subtract(*n2);
    Number* mul = n1->multiply(*n2);
    Number* div = n1->divide(*n2);

    std::cout << "\n============================ Resultados ============================\n";
    std::cout << "\nPrimer número:  " << n1->toString() << "\n";
    std::cout << "Segundo número: " << n2->toString() << "\n\n";

    std::cout << "  La suma entre los números ingresados es:        ";
    if (sum) std::cout << sum->toString() << "\n";
    else std::cout << "Operación inválida\n";

    std::cout << "  La resta entre los números ingresados es:       ";
    if (sub) std::cout << sub->toString() << "\n";
    else std::cout << "Operación inválida\n";

    std::cout << "  La multiplicación entre los números es:         ";
    if (mul) std::cout << mul->toString() << "\n";
    else std::cout << "Operación inválida\n";

    std::cout << "  La división entre los números ingresados es:    ";
    if (div) std::cout << div->toString() << "\n";
    else std::cout << "Operación inválida (división por cero o tipo no soportado)\n";

    std::cout << "====================================================================\n";

    // Liberar memoria
    delete n1;
    delete n2;
    delete sum;
    delete sub;
    delete mul;
    delete div;

    return 0;
}
