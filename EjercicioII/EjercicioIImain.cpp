#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include "EjercicioII.hpp"
#include <memory>


int main(){
    int option;
    std::vector<std::shared_ptr<Course>> coursesList;
    std::vector<std::shared_ptr<Student>> studentsList;

    do {
        std::cout << "================== Opciones ===================" << std::endl;
        std::cout << "Selecciona una opción: \n"<< std::endl;
        std::cout << "1. Crear curso" << std::endl;
        std::cout << "2. Crear alumno" << std::endl;
        std::cout << "3. Verificar si un curso está lleno" << std::endl;
        std::cout << "4. Inscribir alumno a curso existente" << std::endl;
        std::cout << "5. Desinscribir alumno de curso existente" << std::endl;
        std::cout << "6. Mostrar cursos" << std::endl;
        std::cout << "7. Mostrar alumnos" << std::endl;
        std::cout << "8. Buscar alumno en curso" << std::endl;
        std::cout << "9. Mostrar información de curso" << std::endl;
        std::cout << "10. Mostrar información de estudiante" << std::endl;
        std::cout << "11. Crear curso con uso de copia" << std::endl;
        std::cout << "12. Salir" << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "Opción seleccionada: ";

        std::cin >> option;
        std::cout << "=============================================\n" << std::endl;

        switch (option){
            case 1:
                createCourse(coursesList, studentsList);
        
                break;
            
            case 2:
                createStudent(studentsList);
                break;
            
            case 3:
                option3(coursesList);
                break;

            case 4:
                option4(coursesList, studentsList);
                break;
        
            case 5:
                option5(coursesList, studentsList);
                break;

            case 6:
                showCourses(coursesList, studentsList);
                break;

            case 7:
                showStudents(studentsList);
                break;

            case 8:
                option8(coursesList, studentsList);
                break;

            case 9:
                option9(coursesList);
                break;

            case 10:
                option10(studentsList);
                break;
            
            case 11:
                option11(coursesList, studentsList);
                break;
                
            case 12:
                std::cout << "Saliendo del programa..." << std::endl;
                break;

            default:
                std::cout << "Opción no válida. Por favor, selecciona una de las opciones." << std::endl;
                break;

        }

    } while (option != 12);

    return 0;
}