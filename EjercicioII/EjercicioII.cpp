#include <iostream>
#include "EjercicioII.hpp"
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>

// ===================== CURSO =====================

// Constructores de la clase Course
Course::Course() : name(""), profesor(""), students({}), maxStudents(0) {}
Course::Course(std::string name, std::string profesor, std::vector<std::shared_ptr<Student>> students, int maxStudents)
                : name(name), profesor(profesor), students(students), maxStudents(maxStudents) {}

// Método para buscar a un estudiante en un curso específico, devolviendo estudiante
std::shared_ptr<Student> Course::objectStudentInTheCourse(int filenumber) {
    for (const auto& student : students) {
        if (student->filenumber == filenumber) return student;
    }

    return nullptr;

}

/*
    Para cada función que requiriese el buscar a un elemento se podría usar "std::find" o "std::find_if", pero como no tenía claro si era la idea utilizarlo para este Homework II (sé que lo vimos en alguna clase, pero tengo conocimiento del uso de "find" desde antes y creo que no vimos find_if), decidí no utilizarlo. De igual manera quiero dejar claro que no sería muy complicado cambiar esto, dejo como ejemplo esta misma función pero con uso de "find_if":

    std::shared_ptr<Student> Course::objectStudentInTheCourse(int filenumber) {
        auto it = std::find_if(students.begin(), students.end(), [filenumber](const std::shared_ptr<Student>& Student) {
            return Student->filenumber == filenumber;
        });
        return (it != students.end()) ? *it : nullptr;
    }
*/

// Método para mostrar a los estudiantes en un curso y su calificación
void Course::showCourseGrades() {
    int studentNumber = 1;
    for (const auto& student : students) {
        std::cout << "Estudiante N°" << studentNumber++ << ": " << std::endl;
        std::cout << "  Legajo: " << student->filenumber << std::endl;
        std::cout << "  Nombre completo: " << student->name << " " << student->lastname << std::endl;

        bool gradeFound = false;
        for (const auto& grade : student->courseGrades) {
            if (grade.first == name) {
                std::cout << "  Nota en el curso: " << (grade.second.has_value() ? std::to_string(grade.second.value()) : "No asignada") << std::endl;
                gradeFound = true;
                break;

            }

        }

        if (!gradeFound) std::cout << "  Nota en el curso: No encontrada" << std::endl;

    }
}

// Método para buscar a un estudiante en un curso específico
void Course::searchStudentInCourse(int filenumber) {
    auto student = objectStudentInTheCourse(filenumber);
    std::cout << "\nEl estudiante con legajo " << filenumber << (student ? ", llamado " + student->name + " " + student->lastname + ", está inscrito en el curso." : " no está inscrito en el curso.") << std::endl;

}

// Método para agregar un estudiante a un curso
int Course::addStudentToCourse(std::shared_ptr<Student> student) {
    if (students.size() >= static_cast<std::size_t>(maxStudents)) { std::cerr << "Error: El curso ya tiene el número máximo de estudiantes." << std::endl; return -1; }

    if (objectStudentInTheCourse(student->filenumber)) { std::cerr << "Error: El estudiante ya está inscrito en el curso." << std::endl; exit(1); }

    students.push_back(student);

    // Agregar la calificación del curso al estudiante
    int addGradeOption;
    std::cout << "\n¿Desea agregarle calificación al estudiante en este curso?" << std::endl;
    std::cout << "1. Sí" << std::endl;
    std::cout << "2. No" << std::endl;
    std::cout << "\n=============================================" << std::endl;
    std::cout << "Opción seleccionada: ";
    std::cin >> addGradeOption;
    std::cout << "=============================================\n" << std::endl;

    if (addGradeOption == 1) {
        float grade;
        std::cout << "Ingrese la calificación para el curso: ";
        std::cin >> grade;

        if (grade>= 0 && grade <= 10) {
            student->addCourseGrade(name, grade);
            std::cout << "\nCalificación agregada al estudiante." << std::endl;

        } else {
            std::cerr << "Error: La calificación debe estar entre 0 y 10." << std::endl;
            exit(1);

        }

    } else {
        student->courseGrades.push_back(std::make_pair(name, std::nullopt));
        std::cout << "No se asignó calificación al estudiante." << std::endl;
        
    }

    std::cout << "Estudiante agregado al curso exitosamente." << std::endl;
    return 0;

}

// Método para eliminar un estudiante de un curso
void Course::removeStudent(std::shared_ptr<Student> student) {
    for (auto element = students.begin(); element != students.end(); ++element) {
        if (*element == student) { students.erase(element); break; }
    }
}

// Método para mostrar la información de un curso específico
void Course::showCourse() {
    std::cout << "Nombre del curso: " << name << ", Profesor: " << profesor << ", Máximo de estudiantes: " << maxStudents << std::endl;
    std::cout << "Información de estudiantes en el curso:" << std::endl;
    showCourseGrades();
}

// Método para verificar si un curso está lleno
void Course::isCourseFull() {
    std::cout << (students.size() >= static_cast<std::size_t>(maxStudents) ? "\nEl curso ya tiene el número máximo de estudiantes." : "\nEl curso no está lleno. Cuenta con " + std::to_string(students.size()) + " estudiantes.") << std::endl;
    std::cout << "\n===============================================\n" << std::endl;

}

// Método para crear una copia de un curso
std::shared_ptr<Course> Course::copyCourse() {
    return std::make_shared<Course>(*this);
}

// ===================== ESTUDIANTE =====================

// Constructores de la clase Student
Student::Student() : name(""), lastname(""), filenumber(0), courseGrades({}) {}
Student::Student(std::string name, std::string lastname, int filenumber, std::vector<std::pair<std::string, std::optional<float>>> courseGrades)
                : name(name), lastname(lastname), filenumber(filenumber), courseGrades(courseGrades) {}

// Método para mostrar la información de un estudiante
void Student::showStudent() const {
    std::cout << "Legajo: " << filenumber << ", Nombre: " << name << ", Apellido: " << lastname << ", Notas: [";
    for (const auto& grade : courseGrades) {
        std::cout << "_ " << grade.first << ": ";
        if (grade.second.has_value()) {
            std::cout << grade.second.value() << ". ";
        } else {
            std::cout << "Calificación no asignada. ";
        }
    }

    std::cout << "], Promedio (GPA): " << calculateGPA() << std::endl;

}

// Método para calcular el promedio de calificaciones de un estudiante
float Student::calculateGPA() const {
    if (courseGrades.empty()) return 0.0f; // Si no hay calificaciones, el promedio es 0

    float total = 0.0f;
    int count = 0;
    for (const auto& grade : courseGrades) {
        // Solo suma las calificaciones que son válidas (no nulas)
        if (grade.second.has_value()) total += grade.second.value(), count++;
    }

    return count > 0 ? total / count : 0.0f; // Calcula el promedio solo si hay calificaciones válidas

}

// Método para agregar una calificación de curso a un estudiante
int Student::addCourseGrade(const std::string courseName, std::optional<float> grade) {
    for (auto& pair : courseGrades) {
        if (pair.first == courseName) {
            if (!pair.second.has_value()) {
                pair.second = grade;

                std::cerr << "Se agregó calificación para el estudiante en el curso " << courseName << "." << std::endl;
                return 0;
            }

            std::cerr << "Error: Ya existe una entrada para el curso " << courseName << "." << std::endl;
            exit(1);
        }
    }

    courseGrades.push_back(std::make_pair(courseName, grade));
    return 0;

}

// ===================== FUNCIONES DE MENÚ =====================

// Función para buscar a un estudiante por su número de legajo
std::shared_ptr<Student> searchStudent(const std::vector<std::shared_ptr<Student>> &studentsList, int filenumber){
    for (const auto& student : studentsList) {
        if (student->filenumber == filenumber) return student;
    }

    return nullptr;
    
}

// Función para buscar un curso por su nombre
std::shared_ptr<Course> searchCourse(const std::vector<std::shared_ptr<Course>> &coursesList, const std::string &courseName) {
    for (const auto& course : coursesList) {
        return (course->name == courseName) ? course : nullptr;
    }

    return nullptr;

}

// Función para imprimir los estudiantes de un curso en orden
void Course::printStudentsInOrder() const {
    std::vector<Student*> studentPointers;

    for (const auto& student : students) {
        studentPointers.push_back(student.get());
    }

    for (size_t i = 0; i < studentPointers.size(); ++i) {
        for (size_t j = i + 1; j < studentPointers.size(); ++j) {
            if (*studentPointers[j] < *studentPointers[i]) { // Uses the overloaded '<'
                Student* temp = studentPointers[i];
                studentPointers[i] = studentPointers[j];
                studentPointers[j] = temp;
            }
        }
    }

    for (const auto& student : studentPointers) {
        std::cout << *student << std::endl; // Uses the overloaded '<<'
    }

}

// Función para crear un curso
int createCourse(std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string name;
    std::string profesor;
    int maxStudents;
    int yesNo;
    std::vector<std::shared_ptr<Student>> students;

    std::cout << "\n================ Crear curso ===============\n" << std::endl;
    std::cout << "Nombre del curso: ";
    std::cin >> name;
    std::cout << "Nombre del profesor: ";
    std::cin >> profesor;
    std::cout << "¿Cuántos estudiantes tendrá como máximo este curso?: ";
    std::cin >> maxStudents;

    if (maxStudents <= 0) { std::cerr << "Error: El número máximo de estudiantes debe ser mayor que 0." << std::endl; return -1; }

    std::cout << "\n¿Desea ingresar estudiantes al curso?" << std::endl;
    std::cout << "1. Sí" << std::endl;
    std::cout << "2. No" << std::endl;
    std::cout << "\n=============================================" << std::endl;
    std::cout << "Opción seleccionada: ";
    std::cin >> yesNo;
    std::cout << "=============================================\n" << std::endl;

    // Crear el curso inicialmente con el vector de estudiantes vacío
    auto newCourse = std::make_shared<Course>(name, profesor, std::vector<std::shared_ptr<Student>>(), maxStudents);
    coursesList.push_back(newCourse);

    // Verifica si yesNo es 1
    while (yesNo == 1) {
        int studentFilenumber;
        std::cout << "Ingrese el número de legajo del estudiante: ";
        std::cin >> studentFilenumber;
        auto existingStudent = searchStudent(studentsList, studentFilenumber);

        if (existingStudent) {
            newCourse->addStudentToCourse(existingStudent);

        } else {
            std::cerr << "Error: No se encontró un estudiante con ese número de legajo." << std::endl;
        }

        std::cout << "\n¿Desea agregar otro estudiante?" << std::endl;
        std::cout << "1. Sí" << std::endl;
        std::cout << "2. No" << std::endl;
        std::cout << "\n=============================================" << std::endl;
        std::cout << "Opción seleccionada: ";
        std::cin >> yesNo;
        std::cout << "=============================================\n" << std::endl;

    }

    // Mensaje final según si se ingresaron estudiantes o no
    if (!newCourse->students.empty()) std::cout << "Estudiantes ingresados correctamente." << std::endl;

    std::cout << "\n===============================================" << std::endl;
    std::cout << "Curso creado exitosamente." << std::endl;
    std::cout << "===============================================\n" << std::endl;

    return 0;

}

// Función para crear un estudiante
int createStudent(std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string name;
    std::string lastname;
    int filenumber;
    std::vector<std::pair<std::string, std::optional<float>>> courseGrades;

    std::cout << "\n================= Crear estudiante ===============\n" << std::endl;
    std::cout << "Nombre del estudiante: ";
    std::cin >> name;
    std::cout << "Apellido del estudiante: ";
    std::cin >> lastname;
    std::cout << "Número de legajo del estudiante: ";
    std::cin >> filenumber;

    // Verifica si el número de legajo ya existe
    if (searchStudent(studentsList, filenumber)) { std::cerr << "Error: Ya existe un estudiante con ese número de legajo." << std::endl; exit(1); }

    // Crear el nuevo estudiante
    auto newStudent = std::make_shared<Student>(name, lastname, filenumber, courseGrades);
    studentsList.push_back(newStudent);

    std::cout << "\n===============================================" << std::endl;
    std::cout << "Estudiante creado exitosamente." << std::endl;
    std::cout << "===============================================\n" << std::endl;

    return 0;

}

// Función para mostrar los cursos con todos sus datos
/*
    Aquí se utiliza la función de mostrar a los estudiantes pertenecientes a un curso de manera ordenada alfabéticamente, ya que pensé que al listar los estudiantes sería mejor verlos en orden de inserción.
*/
void showCourses(std::vector<std::shared_ptr<Course>> &coursesList, std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string courseName;
    
    std::cout << "\n=================== Cursos ===================\n" << std::endl;

    if (coursesList.empty()) std::cout << "No hay cursos registrados." << std::endl;

    for (size_t i = 0; i < coursesList.size(); i++) {
        auto students = coursesList[i]->students;
        std::cout << "N°: " << i+1 << " ========================================" << std::endl;
        std::cout << "Nombre: " << coursesList[i]->name << std::endl;
        std::cout << "Profesor: " << coursesList[i]->profesor << std::endl;
        std::cout << "Número máximo de estudiantes: " << coursesList[i]->maxStudents << std::endl;
        std::cout << "Estudiantes: " << std::endl;
        coursesList[i]->printStudentsInOrder();
        std::cout << "===============================================\n" << std::endl;
    }
}

// Función para mostrar a todos los estudiantes
void showStudents(std::vector<std::shared_ptr<Student>> &studentsList) { // <== Se pasa por referencia
    std::cout << "\n================= Estudiantes =================\n" << std::endl;

    if (studentsList.empty()) std::cout << "No hay estudiantes registrados." << std::endl;

    for (size_t i = 0; i < studentsList.size(); i++) {
        std::cout << "N°: " << i+1 << " ========================================================================================" << std::endl;
        studentsList[i]->showStudent();
        std::cout << "===============================================================================================\n" << std::endl;
    }
}

int option3(std::vector<std::shared_ptr<Course>> &coursesList){
    std::string courseName;
    std::cout << "\n================= Verificar si un curso está lleno ===============\n" << std::endl;
    std::cout << "Inserte el nombre del curso: ";
    std::cin >> courseName;

    auto course = searchCourse(coursesList, courseName);
    if (!course) { std::cerr << "Error: Curso no encontrado." << std::endl; exit(1); }

    course->isCourseFull();
    return 0;

}

// Función para agregar un estudiante a un curso
int option4(const std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string courseName;
    int studentFileNumber;
    std::cout << "\n======== Inscribir estudiante a curso existente ========\n" << std::endl;
    std::cout << "Inserte el nombre del curso: ";
    std::cin >> courseName;
    auto course = searchCourse(coursesList, courseName);

    if (!course) { std::cerr << "Error: Curso no encontrado." << std::endl; exit(1); }

    std::cout << "Inserte el legajo del estudiante a agregar al curso: ";
    std::cin >> studentFileNumber;
    auto student = searchStudent(studentsList, studentFileNumber);

    if (!student) { std::cerr << "Error: Estudiante no encontrado." << std::endl; exit(1); }

    course->addStudentToCourse(student);
    std::cout << "Estudiante agregado al curso exitosamente." << std::endl;
    std::cout << "===============================================\n" << std::endl;

    return 0;

}

// Función para eliminar un estudiante de un curso
int option5(std::vector<std::shared_ptr<Course>> &coursesList, std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string courseName;
    int studentFileNumber;
    std::cout << "\n======== Desinscribir estudiante de curso existente =====\n" << std::endl;
    std::cout << "Inserte el nombre del curso: ";
    std::cin >> courseName;

    auto course = searchCourse(coursesList, courseName);
    if (!course) { std::cerr << "Error: Curso no encontrado." << std::endl; exit(1); }

    std::cout << "Inserte el legajo del estudiante: ";
    std::cin >> studentFileNumber;
    auto student = searchStudent(studentsList, studentFileNumber);

    if (!student) { std::cerr << "Error: Estudiante no encontrado." << std::endl; exit(1); }

    course->removeStudent(student);
    std::cout << "Estudiante eliminado del curso exitosamente." << std::endl;
    std::cout << "===============================================\n" << std::endl;

    return 0;

}

// Función para buscar un estudiante en un curso específico
int option8(const std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string courseName;
    int studentFileNumber;

    std::cout << "\n=========== Buscar estudiante en un curso ===========\n" << std::endl;
    std::cout << "Ingrese el nombre del curso: ";
    std::cin >> courseName;

    auto course = searchCourse(coursesList, courseName);
    if (!course) { std::cerr << "Error: Curso no encontrado." << std::endl; exit(1); }

    std::cout << "Ingrese el número de legajo del estudiante: ";
    std::cin >> studentFileNumber;

    auto student = searchStudent(studentsList, studentFileNumber);
    if (!student) { std::cerr << "Error: Estudiante no encontrado." << std::endl; exit(1); }

    course->searchStudentInCourse(studentFileNumber);
    std::cout << "===============================================\n" << std::endl;

    return 0;

}

// Función para mostrar la información de un curso específico
int option9(const std::vector<std::shared_ptr<Course>> &coursesList) {
    std::string courseName;

    std::cout << "\n=============== Mostrar información de curso =============\n" << std::endl;
    std::cout << "Ingrese el nombre del curso: ";
    std::cin >> courseName;

    auto course = searchCourse(coursesList, courseName);
    if (!course) { std::cerr << "Error: Curso no encontrado." << std::endl; exit(1); }

    course->showCourse();
    std::cout << "===============================================\n" << std::endl;

    return 0;

}

// Función para mostrar la información de un estudiante específico
int option10(const std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string studentName;
    int studentFileNumber;

    std::cout << "\n============ Mostrar información de estudiante ==========\n" << std::endl;
    std::cout << "Ingrese el número de legajo del estudiante: ";
    std::cin >> studentFileNumber;

    auto student = searchStudent(studentsList, studentFileNumber);
    if (!student) { std::cerr << "Error: Estudiante no encontrado." << std::endl; exit(1); }

    student->showStudent();
    return 0;

}

// Función para crear copia de objeto curso
/*
    Decidí usar una copia del tipo Shallow Copy, ya que no se tienen punteros a perder durante la copia, de ser así hubiese utilizado un Deep Copy.
    No se necesita liberar memoria, ya que los punteros son compartidos y no se pierde la referencia a los objetos originales. La realización de un Shallow Copy es el más sencillo que hemos visto, por lo que creo que se entiende lo suficientemente bien en el código.
*/
int option11(std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList) {
    std::string courseName;
    std::cout << "\n================= Crear curso con uso de copia ===============\n" << std::endl;
    std::cout << "Inserte el nombre del curso del que desea hacer la copia: ";
    std::cin >> courseName;

    auto course = searchCourse(coursesList, courseName);
    if (!course) { std::cerr << "Error: Curso no encontrado." << std::endl; exit(1); }

    auto copiedCourse = course->copyCourse();
    coursesList.push_back(copiedCourse);

    std::cout << "Modifique el nombre del nuevo curso: ";
    std::cin >> copiedCourse->name;
    std::cout << "Modifique el nombre profesor del nuevo curso: ";
    std::cin >> copiedCourse->profesor;
    std::cout << "Modifique el número máximo de estudiantes del nuevo curso: ";
    std::cin >> copiedCourse->maxStudents;

    if (copiedCourse->maxStudents <= 0) { std::cerr << "Error: El número máximo de estudiantes debe ser mayor que 0." << std::endl; exit(1); }

    // Agregar el nuevo curso y calificación a los estudiantes del curso original
    for (const auto& student : course->students) {
        auto existingStudent = searchStudent(studentsList, student->filenumber);
        if (existingStudent) {
            for (const auto& grade : student->courseGrades) {
                if (grade.first == course->name) { existingStudent->addCourseGrade(copiedCourse->name, grade.second); break; }
            }
        }
    }

    std::cout << "\n===============================================" << std::endl;
    std::cout << "Curso copiado exitosamente." << std::endl;
    std::cout << "===============================================\n" << std::endl;

    return 0;

}