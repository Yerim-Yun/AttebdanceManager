#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

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

enum Grade {
	NORMAL = 0,
	GOLD,
	SILVER,
};

map<string, int> playerID;
int id_cnt = 0;

int cntOfWeek[100][100];
int points[100];
int grade[100];
string names[100];

int cntOfWed[100];
int cntOfWeekend[100];

DayOfWeek getDayOfWeek(const string& day) {
	if (day == "monday") return MONDAY;
	if (day == "tuesday") return TUESDAY;
	if (day == "wednesday") return WEDNESDAY;
	if (day == "thursday") return THURSDAY;
	if (day == "friday") return FRIDAY;
	if (day == "saturday") return SATURDAY;
	if (day == "sunday") return SUNDAY;
	return DAY_COUNT;
}

bool isExistPlayer(const string& playerName) {
	return (playerID.count(playerName) != 0);
}

void updatePlayerID(std::string& playerName)
{
	//ID 부여
	if (!isExistPlayer(playerName)) {
		playerID.insert({ playerName, ++id_cnt });
		names[id_cnt] = playerName;
	}
}

int getPointPerDay(DayOfWeek day) {
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

void UpdatePlayerPoint(int id, DayOfWeek dayOfWeek)
{
	points[id] += getPointPerDay(dayOfWeek);
}

void UpdatePlayerCntOfAttendance(int id, DayOfWeek dayOfWeek)
{
	if (dayOfWeek == WEDNESDAY)
		cntOfWed[id] += 1;

	if (dayOfWeek == SATURDAY || dayOfWeek == SUNDAY)
		cntOfWeekend[id] += 1;

	//사용자ID별 요일 데이터에 1씩 증가
	cntOfWeek[id][dayOfWeek] += 1;
}

void processAttendanceData(string playerName, string day) {
	DayOfWeek dayOfWeek = getDayOfWeek(day);
	updatePlayerID(playerName);

	int id = playerID[playerName];
	UpdatePlayerPoint(id, dayOfWeek);
	UpdatePlayerCntOfAttendance(id, dayOfWeek);
}

void addBonusPoints(int id)
{
	if (cntOfWeek[id][WEDNESDAY] > 9)
		points[id] += 10;

	if (cntOfWeek[id][SATURDAY] + cntOfWeek[id][SUNDAY] > 9)
		points[id] += 10;
}

void gradePoints(int id)
{
	if (points[id] >= 50) {
		grade[id] = GOLD;
	}
	else if (points[id] >= 30) {
		grade[id] = SILVER;
	}
	else {
		grade[id] = NORMAL;
	}
}

string getGradeString(int grade) {
	switch (grade) {
	case GOLD:
		return "GOLD";
	case SILVER:
		return "SILVER";
	default:
		return "NORMAL";
	}

}
void printPlayerData(int id)
{
	cout << "NAME : " << names[id] << ", ";
	cout << "POINT : " << points[id] << ", ";
	cout << "GRADE : " << getGradeString(grade[id]) << "\n";
}

void analyzePlayersPoints()
{
	for (int id = 1; id <= id_cnt; id++) {
		addBonusPoints(id);
		gradePoints(id);
		printPlayerData(id);
	}
}

void processAttendanceFile() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string name, day;
		fin >> name >> day;
		processAttendanceData(name, day);
	}
}

bool isRemovedPlayer(int id)
{
	return (grade[id] != GOLD && grade[id] != SILVER && cntOfWed[id] == 0 && cntOfWeekend[id] == 0);
}

void printRemovedPlayer()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int id = 1; id <= id_cnt; id++) {
		if (isRemovedPlayer(id)) {
			std::cout << names[id] << "\n";
		}
	}
}

int main() {
	processAttendanceFile();
	analyzePlayersPoints();
	printRemovedPlayer();
}