#include "player.h"

Player::Player(const std::string& name) : name(name) {}

void Player::setGrade(const IGrade* grade) { this->grade = grade; }

string Player::getName() { return this->name; }
int Player::getPoints() { return this->points; }
string Player::getGradeName() { return (grade) ? grade->getGradeName() : "Unknown"; }

int Player::getAttendanceCnt(int day) {
    if (cntOfWeek.count(day)) {
        return cntOfWeek.at(day);
    }
    return 0;
}

void Player::addPoints(int points) {
    this->points += points;
}

void Player::addAttendance(int day)
{
	this->cntOfWeek[day]++;
}
