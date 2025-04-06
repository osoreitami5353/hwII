#ifndef EJERCICIOII_H
#define EJERCICIOII_H
#include <iostream>
#include <vector>
#include <memory>
#include <optional>

class Student;

class Course {
    public:
        /*
            Me  tomé el atrevimiento de en vez que todos los cursos tengan un maximo de estudiantes = 20, que cada curso tenga su propio maximo de estudiantes. Espero no sea gran problema, porque creo que dejarlo como un valor estático tendría una dificultad menor o como mucho del mismo nivel.
        */
        std::string name;
        std::string profesor;
        std::vector<std::shared_ptr<Student>> students;
        int maxStudents;
        
        Course();
        Course(std::string name, std::string profesor, std::vector<std::shared_ptr<Student>> students, int maxStudents);
        
        std::shared_ptr<Student> objectStudentInTheCourse(int filenumber);
        void showCourseGrades();
        void searchStudentInCourse(int filenumber);
        int addStudentToCourse(std::shared_ptr<Student> student);
        void removeStudent(std::shared_ptr<Student> student);
        void showCourse();
        void isCourseFull();
        std::shared_ptr<Course> copyCourse();
        void printStudentsInOrder() const;
};

class Student {
    public:
        std::string name;
        std::string lastname;
        int filenumber;
        std::vector<std::pair<std::string, std::optional<float>>> courseGrades;

        Student();
        Student(std::string name, std::string lastname, int filenumber, std::vector<std::pair<std::string, std::optional<float>>> courseGrades);
        
        // Sobrecarga del operador '<' para ordenar por nombre
        bool operator<(const Student& another) const {
            return name < another.name;
        }

        // Sobrecarga del operador '<<' para imprimir un estudiante
        friend std::ostream& operator<<(std::ostream& os, const Student& s) {
            os << "     Legajo: " << s.filenumber << ", Nombre: " << s.name << ", Apellido: " << s.lastname;
            return os;
        }

        void showStudent() const;
        float calculateGPA() const;
        int addCourseGrade(const std::string courseName, std::optional<float> grade);
};

std::shared_ptr<Student> searchStudent(const std::vector<std::shared_ptr<Student>> &studentsList, int filenumber);
std::shared_ptr<Course> searchCourse(const std::vector<std::shared_ptr<Course>> &coursesList, const std::string &courseName);

void printOrderedStudents(std::vector<Student*> students);

int createCourse(std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList);
int createStudent(std::vector<std::shared_ptr<Student>> &studentsList);

void showCourses(std::vector<std::shared_ptr<Course>> &coursesList, std::vector<std::shared_ptr<Student>> &studentsList);
void showStudents(std::vector<std::shared_ptr<Student>> &studentsList);

int option3(std::vector<std::shared_ptr<Course>> &coursesList);
int option4(const std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList);
int option5(std::vector<std::shared_ptr<Course>> &coursesList, std::vector<std::shared_ptr<Student>> &studentsList);
int option8(const std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList);
int option9(const std::vector<std::shared_ptr<Course>> &coursesList);
int option10(const std::vector<std::shared_ptr<Student>> &studentsList);
int option11(std::vector<std::shared_ptr<Course>> &coursesList, const std::vector<std::shared_ptr<Student>> &studentsList);

#endif