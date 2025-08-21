#pragma once

#include <string>
#include <vector>
#include "player.h"
#include "grade.h"

using namespace std;

enum DayOfWeek {
	MONDAY = 0,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
	DAY_COUNT
};

class IPolicy {
	public:
	virtual ~IPolicy() = default;
	virtual void apply(Player& player) = 0;
};

class DayPointPolicy : public IPolicy {
public:
	int getPointPerDay(int day);
	void apply(Player& player) override;
};

class BonusPointPolicy : public IPolicy {
public:
    void apply(Player& player) override;
};

class GradePolicy : public IPolicy {
public:
	GradePolicy(vector<IGrade*>& grades) : grades(grades) {};
	void apply(Player& player) override;
private:
	vector<IGrade*> grades;
};