#include <iostream>
#include "EjercicioI.hpp"
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

// ===================== CONSTRUCTORES =====================

// Constructores
Time::Time(){
    hours = 0;
    minutes = 0;
    seconds = 0;
    ap = 'a';
}

Time::Time(int h){
    hours = h;
    minutes = 0;
    seconds = 0;
    ap = 'a';
}

Time::Time(int h, int m){
    hours = h;
    minutes = m;
    seconds = 0;
    ap = 'a';
}

Time::Time(int h, int m, int s){
    hours = h;
    minutes = m;
    seconds = s;
    ap = 'a';
}

Time::Time(int h, int m, int s, char ap){
    hours = h;
    minutes = m;
    seconds = s;
    this->ap = ap;
}

// ===================== TIEMPO =====================

// Método para obtener la hora individualmente
int Time::getHours() const {
    std::cout << "Hora: " << std::setw(2) << std::setfill('0') << hours << std::endl;
    return hours;

}

// Método para obtener los minutos individualmente
int Time::getMinutes() const {
    std::cout << "Minutos: " << std::setw(2) << std::setfill('0') << minutes << std::endl;
    return minutes;

}

// Método para obtener los segundos individualmente
int Time::getSeconds() const {
    std::cout << "Segundos: " << std::setw(2) << std::setfill('0') << seconds << std::endl;
    return seconds;

}

// Método para obtener si se trata de AM/PM individualmente
char Time::getAP() const {
    std::string ampm;
    
    if (ap == 'a') {
        ampm = "A.M.";

    } else if (ap == 'p') {
        ampm = "P.M.";

    }

    std::cout << "A.M./P.M.: " << ampm << std::endl;
    return ap;

}

// Método para obtener la hora completa
void Time::getTimeInfo() const {
    std::string ampm;
    
    if (ap == 'a') {
        ampm = "A.M.";

    } else if (ap == 'p') {
        ampm = "P.M.";

    }

    std::cout << "Hora completa: " << std::setw(2) << std::setfill('0') << hours << "h, " << std::setw(2) << std::setfill('0') << minutes << "m, " << std::setw(2) << std::setfill('0') << seconds << "s " << ampm << std::endl;
    
}

// Método para obtener la hora completa en formato 24hs
void Time::get24TimeInfo() const {
    int h24;
    std::string ampm;
    
    if (ap == 'a') {
        ampm = "A.M.";

    } else if (ap == 'p') {
        ampm = "P.M.";

    }

    if (ap == 'a') {
        h24 = hours;

    } else if (ap == 'p') {
        h24 = hours + 12;

    }

    std::cout << "Hora completa en formato 24hs: " << std::setw(2) << std::setfill('0') << h24 << "h, " << std::setw(2) << std::setfill('0') << minutes << "m, " << std::setw(2) << std::setfill('0') << seconds << "s." << std::endl;
}

// Método para modificar el tiempo ingresado
int Time::modifyTime() {
    int h, m, s;
    std::string ampm;
    std::string input;
    std::vector<std::string> words;

    std::cout << "Introduce el nuevo tiempo: ";

    std::cin.clear();  // Limpia el estado de error
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descarta la entrada inválida
    
    std::getline(std::cin, input);

    // Uso de std::istringstream para dividir una cadena de texto (input) en palabras separadas por espacios, y luego guardarlas en un vector de strings
    std::istringstream ss(input);
    std::string word;
    
    while (ss >> word) {
        words.push_back(word);
    }

    if (words.size() == 4){
        char ap2;

        if (words[3] == "AM" || words[3] == "am") {
            ap2 = 'a';
        } else if (words[3] == "PM" || words[3] == "pm") {
            ap2 = 'p';
        } else {
            std::cerr << "Error: Formato de AM/PM no válido." << std::endl;
            exit(1);
        }

        h = std::stoi(words[0]);
        m = std::stoi(words[1]);
        s = std::stoi(words[2]);
        
        hours = h;
        minutes = m;
        seconds = s;
        ap = ap2;

        validateAP(words, *this);
        validateSeconds(*this);
        validateMinutes(*this);
        validateHoursI(*this);

        coutsModification();

    } else if (words.size() == 3){
        h = std::stoi(words[0]);
        m = std::stoi(words[1]);
        s = std::stoi(words[2]);

        hours = h;
        minutes = m;
        seconds = s;
        ap = 'a';
        
        validateHoursI(*this);
        validateMinutes(*this);
        validateSeconds(*this);
        
        coutsModification();

    } else if (words.size() == 2){
        h = std::stoi(words[0]);
        m = std::stoi(words[1]);
        
        hours = h;
        minutes = m;
        seconds = 0;
        ap = 'a';

        validateHoursI(*this);
        validateMinutes(*this);
        
        coutsModification();

    } else if (words.size() == 1){
        h = std::stoi(words[0]);
        
        hours = h;
        minutes = 0;
        seconds = 0;
        ap = 'a';

        validateHoursI(*this);
        
        coutsModification();

    } else {

        std::cerr << "Error: Formato de hora no válido." << std::endl;
        exit(1);
    }

    return 0;

}

// ===================== VALIDACIONES DE ENTRADA =====================

// Validación de horas para formato am/pm
int validateHoursI(Time &t) {
    if (t.hours < 0 || t.hours > 12) {
        std::cout << "Error: La hora debe estar entre 0 y 12 si introduce un valor am/pm." << std::endl;
        exit(1);
    }

    return 0;
}

// Validación de minutos 
int validateMinutes(Time &t) {
    if (t.minutes < 0) {
        std::cout << "Error: Los minutos no pueden ser negativos." << std::endl;
        exit(1);

    } else if (t.minutes >= 60) {
        std::cout << "Los minutos excedidos fueron convertidos a horas." << std::endl;
        t.hours += t.minutes / 60;
        t.minutes = t.minutes % 60;

    }

    return 0;
}

// Validación de segundos
int validateSeconds(Time &t) {
    if (t.seconds < 0) {
        std::cout << "Error: Los segundos no pueden ser negativos." << std::endl;
        exit(1);

    } else if (t.seconds >= 60) {
        std::cout << "Los segundos excedidos fueron convertidos a minutos." << std::endl;
        t.minutes += t.seconds / 60;
        t.seconds = t.seconds % 60;

    }
    
    return 0;
}

// Validación de formato am/pm
int validateAP(std::vector<std::string> &words, Time &t) {
    char ap;

    if (words[3] == "AM" || words[3] == "am") {
        ap = 'a';
    } else if (words[3] == "PM" || words[3] == "pm") {
        ap = 'p';
    } else {
        std::cerr << "Error: Formato de AM/PM no válido." << std::endl;
        exit(1);
    }

    t.ap = ap;
    return 0;

}


// ===================== Mensajes de entrada y modificación =====================

// Mensajes de entrada
void coutsEntry() {
    std::cout << "Hora introducida correctamente." << std::endl;
    std::cout << "Presione 'Enter' para ver más opciones..." << std::endl;
    std::cout << "=============================================" << std::endl;
}

// Mensajes de modificación
void coutsModification() {
    std::cout << "Tiempo modificada correctamente." << std::endl;
    std::cout << "Presione 'Enter' para ver más opciones..." << std::endl;
    std::cout << "=============================================" << std::endl;
}

// ===================== PRIMER INGRESO DE TIEMPO =====================

// Función para ingresar el tiempo
int timeEntry(std::vector<std::string> &words, Time &tpointer) {
    int h, m, s;
    std::string ampm;

    if (words.size() == 4){
        char ap;
        
        if (words[3] == "AM" || words[3] == "am") {
            ap = 'a';
        } else if (words[3] == "PM" || words[3] == "pm") {
            ap = 'p';
        } else {
            std::cerr << "Error: Formato de AM/PM no válido." << std::endl;
            exit(1);
        }

        h = std::stoi(words[0]);
        m = std::stoi(words[1]);
        s = std::stoi(words[2]);
        Time t(h, m, s, ap);
        
        validateAP(words, t);
        validateSeconds(t);
        validateMinutes(t);
        validateHoursI(t);

        tpointer = t;
        coutsEntry();

    } else if (words.size() == 3){
        h = std::stoi(words[0]);
        m = std::stoi(words[1]);
        s = std::stoi(words[2]);
        Time t(h, m, s);
        t.ap = 'a';
        validateHoursI(t);
        validateMinutes(t);
        validateSeconds(t);
        tpointer = t;
        coutsEntry();

    } else if (words.size() == 2){
        h = std::stoi(words[0]);
        m = std::stoi(words[1]);
        Time t(h, m);
        t.seconds = 0;
        t.ap = 'a';
        validateHoursI(t);
        validateMinutes(t);
        tpointer = t;
        coutsEntry();

    } else if (words.size() == 1){
        h = std::stoi(words[0]);
        Time t(h);
        t.minutes = 0;
        t.seconds = 0;
        t.ap = 'a';
        validateHoursI(t);
        tpointer = t;
        coutsEntry();

    } else {
        std::cerr << "Error: Formato de hora no válido." << std::endl;
        exit(1);

    }

    return 0;

}