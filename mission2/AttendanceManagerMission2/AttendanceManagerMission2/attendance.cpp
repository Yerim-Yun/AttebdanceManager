#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "gmock/gmock.h"
#include "grade.h"
#include "policy.h"
#include "player.h"

using namespace testing;
using namespace std;

class AttendanceManager {
private:
	map<string, Player> players;
	vector<string> playerNames;
	vector<IPolicy*> policies;
public:
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

	bool hasPlayer(const string& name) const {
		return players.count(name) > 0;
	}

	void processFile(const std::string& filename) {
		ifstream fin(filename);
		string name, dayStr;
		while (fin >> name >> dayStr) {
			if (!hasPlayer(name)) {
				playerNames.push_back(name);
				players.emplace(name, Player(name));
			}

			// count attendance
			DayOfWeek day = getDayOfWeek(dayStr);
			players.at(name).addAttendance(day);
		}
	}

	void addPolicy(IPolicy* policy) {
		policies.push_back(policy);
	}

	void applyPolicies()
	{
		for (auto& pair : players) {
			Player& player = pair.second;
			for(auto& policy : policies) {
				policy->apply(player);
			}
		}
	}

	void printPlayerData()
	{
		for (const auto& name : playerNames) {
			Player& player = players.at(name);

			cout << "NAME : " << player.getName() << ", ";
			cout << "POINT : " << player.getPoints() << ", ";
			cout << "GRADE : " << player.getGradeName() << "\n";
		}
	}

	bool isRemovedPlayer(Player& player)
	{
		return (player.getGradeName() != "GOLD" && player.getGradeName() != "SILVER" &&
			player.getAttendanceCnt(WEDNESDAY) == 0 &&
			player.getAttendanceCnt(SATURDAY) == 0 &&
			player.getAttendanceCnt(SUNDAY) == 0);
	}

	void printRemovedPlayer()
	{
		std::cout << "\n";
		std::cout << "Removed player\n";
		std::cout << "==============\n";
		for (auto& pair : players) {
			Player& player = pair.second;
			if (isRemovedPlayer(player)) {
				std::cout << player.getName() << "\n";
			}
		}
	}
};

int main() {
#ifdef _DEBUG
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
#else
	AttendanceManager manager;
	vector<IGrade*> grades = {
	new NormalGrade(),
	new SilverGrade(),
	new GoldGrade(),
	};

	manager.processFile("attendance_weekday_500.txt");

	manager.addPolicy(new DayPointPolicy());
	manager.addPolicy(new BonusPointPolicy());
	manager.addPolicy(new GradePolicy(grades));

	manager.applyPolicies();
	manager.printPlayerData();
	manager.printRemovedPlayer();
#endif
}