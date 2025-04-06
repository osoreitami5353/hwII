#ifndef EJERCICIOI_H
#define EJERCICIOI_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Time {
    public:
        Time();
        Time(int h);
        Time(int h, int m);
        Time(int h, int m, int s);
        Time(int h, int m, int s, char ap);

        int hours;
        int minutes;
        int seconds;
        char ap;

        int getHours() const;
        int getMinutes() const;
        int getSeconds() const;
        char getAP() const;
        void getTimeInfo() const;
        void get24TimeInfo() const;
        int modifyTime();
};

int timeEntry(std::vector <std::string> &words, Time &tpointer);

int validateHoursI(Time &t);
int validateMinutes(Time &t);
int validateSeconds(Time &t);
int validateAP(std::vector <std::string> &words, Time &t);

void coutsEntry();
void coutsModification();

#endif 