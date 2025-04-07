#include <iostream>
#include "EjercicioI.hpp"
#include <limits>
#include <iomanip>
#include <vector>

int main(){
    std::string input;
    std::vector<std::string> words;
    int option;
    Time timeObj;
    Time *tpointer = &timeObj;

    std::cout << "=============================================" << std::endl;
    std::cout<< "======== Bienvenido a la actividad I ========" << std::endl;
    std::cout<< "Introduce el tiempo en el formato: h m s am/pm (Ejemplo: 3 24 16 pm): ";

    std::getline(std::cin, input);

    std::istringstream ss(input);
    std::string word;
    
    while (ss >> word) {
        words.push_back(word);
    }

    timeEntry(words, *tpointer);

    do{
        std::cin.clear();  // Limpia el estado de error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descarta la entrada inválida
        std::cout << "================== Extras ===================" << std::endl;
        std::cout << "Selecciona una opción: "<< std::endl;
        std::cout << "1. Modificar hora" << std::endl;
        std::cout << "2. Mostrar hora individualmente" << std::endl;
        std::cout << "3. Mostrar minutos individualmente" << std::endl;
        std::cout << "4. Mostrar segundos individualmente" << std::endl;
        std::cout << "5. Mostrar ap individualmente" << std::endl;
        std::cout << "6. Mostrar hora completa" << std::endl;
        std::cout << "7. Mostrar hora completa en formato 24." << std::endl;
        std::cout << "8. Ingresar nueva hora." << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "Opción seleccionada: ";

        std::cin >> option;
        std::cout << "=============================================" << std::endl;

        switch (option){
            case 1:
                tpointer->modifyTime();
                std::cout << "\n=============================================" << std::endl;
                std::cout << "Hora modificada correctamente." << std::endl;
                std::cout << "=============================================\n" << std::endl;
                break;
            
            case 2:
                tpointer->getHours();
                break;
            
            case 3:
                tpointer->getMinutes();
                break;
        
            case 4:
                tpointer->getSeconds();
                break;
            
            case 5:
                tpointer->getAP();
                break;
            
            case 6:
                tpointer->getTimeInfo();
                break;

            case 7:
                tpointer->get24TimeInfo();
                break;
            
            case 8: {
                std::cout << "Introduce el tiempo en el formato: h m s am/pm (Ejemplo: 3 24 16 pm): ";

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, input);
            
                std::istringstream ss(input);
                std::string word;
                words.clear(); // Importante: limpiar el vector para no acumular entradas anteriores
            
                while (ss >> word) {
                    words.push_back(word);
                }
            
                timeEntry(words, *tpointer);
                break;

            }
            
            case 9:
                std::cout << "Saliendo del programa..." << std::endl;
                
                break;

            default:
                std::cout << "Opción no válida. Por favor, selecciona una opción de los extras." << std::endl;

                break;

        }

    } while (option != 9);
    
    return 0;
}