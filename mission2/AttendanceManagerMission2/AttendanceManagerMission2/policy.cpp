#include "policy.h"

int DayPointPolicy::getPointPerDay(int day) {
	switch (day) {
	case MONDAY:
	case TUESDAY:
	case THURSDAY:
	case FRIDAY:
		return 1;
	case WEDNESDAY:
		return 3;
	case SATURDAY:
	case SUNDAY:
		return 2;
	default:
		return 0;
	}
}

void DayPointPolicy::apply(Player& player) {
	for (int day = 0; day < DAY_COUNT; ++day) {
		player.addPoints(getPointPerDay(day) * player.getAttendanceCnt(day));
	}
}

void BonusPointPolicy::apply(Player& player) {
	if (player.getAttendanceCnt(WEDNESDAY) > 9)
		player.addPoints(10);

	if (player.getAttendanceCnt(SATURDAY) + player.getAttendanceCnt(SUNDAY) > 9)
		player.addPoints(10);
}

void GradePolicy::apply(Player& player) {
	for (auto it = grades.rbegin(); it != grades.rend(); ++it) {
		if ((*it)->isMeetCriteria(player.getPoints())) {
			player.setGrade(*it);
			return;
		}
	}
}
