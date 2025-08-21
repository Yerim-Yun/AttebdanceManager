#include "grade.h"

string NormalGrade::getGradeName() const {
	return "NORMAL";
}

bool NormalGrade::isMeetCriteria(int points) const {
	return points < 30;
}

string SilverGrade::getGradeName() const {
	return "SILVER";
}

bool SilverGrade::isMeetCriteria(int points) const {
	return points >= 30 && points < 50;
}

string GoldGrade::getGradeName() const {
	return "GOLD";
}

bool GoldGrade::isMeetCriteria(int points) const {
	return points >= 50;
}
