#include "EjercicioIV.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <memory>

int main() {
    int option;

    do {
        std::cout << "================== Menú ===================" << std::endl;
        std::cout << "Seleccione una opción: \n" << std::endl;
        std::cout << "1. Crear cuenta bancaria" << std::endl;
        std::cout << "2. Depositar monto" << std::endl;
        std::cout << "3. Retirar monto" << std::endl;
        std::cout << "4. Mostrar información de cuenta" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "===========================================" << std::endl;
        std::cout << "Opción seleccionada: ";

        std::cin >> option;
        std::cout << "===========================================\n" << std::endl;

        switch (option) {
            case 1: option1(); break;
            case 2: option2(); break;
            case 3: option3(); break;
            case 4: option4(); break;
            case 5: std::cout << "Saliendo del programa..."; break;
            default: std::cout << "\nOpción inválida.\n"; break;
            
        }

        std::cin.clear(); // Limpia estado de error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia buffer
        std::cout << "\n";

    } while (option != 5);

    for (auto acc : savingsAccounts) delete acc;
    for (auto acc : checkingAccounts) delete acc;

    return 0;
}
