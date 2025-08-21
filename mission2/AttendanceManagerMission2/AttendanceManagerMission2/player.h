#pragma once
#include <string>
#include <map>
#include "grade.h"

class Player {
private:
    string name;
    int points = 0;
    map<int, int> cntOfWeek;
    const IGrade* grade = nullptr;
public:
    Player(const std::string& name);

    void setGrade(const IGrade* grade);
    string getName();
    int getPoints();
    string getGradeName();
    int getAttendanceCnt(int day);
    void addPoints(int points);
    void addAttendance(int day);
};