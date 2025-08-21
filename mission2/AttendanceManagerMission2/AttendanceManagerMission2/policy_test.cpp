#include "policy.h"
#include "player.h"
#include "gmock/gmock.h"

using namespace testing;

class PolicyFixture : public ::testing::Test {
public:
	void SetUp() override {
		player = new Player("TestPlayer");
	}
	void setPolicy(IPolicy* policy) {
		this->policy = policy;
	}
	Player* player;
	IPolicy* policy = nullptr;
};

TEST_F(PolicyFixture, getPointPerDay_test){
	DayPointPolicy policy;
	EXPECT_EQ(policy.getPointPerDay(MONDAY), 1);
	EXPECT_EQ(policy.getPointPerDay(TUESDAY), 1);
	EXPECT_EQ(policy.getPointPerDay(WEDNESDAY), 3);
	EXPECT_EQ(policy.getPointPerDay(THURSDAY), 1);
	EXPECT_EQ(policy.getPointPerDay(FRIDAY), 1);
	EXPECT_EQ(policy.getPointPerDay(SATURDAY), 2);
	EXPECT_EQ(policy.getPointPerDay(SUNDAY), 2);
	EXPECT_EQ(policy.getPointPerDay(7), 0); // Invalid day
}

TEST_F(PolicyFixture, DayApplyTest) {
	setPolicy(new DayPointPolicy());
	player->addAttendance(MONDAY); // 1
	player->addAttendance(TUESDAY); // 1
	player->addAttendance(WEDNESDAY); // 3
	player->addAttendance(THURSDAY); // 1
	player->addAttendance(FRIDAY); // 1
	player->addAttendance(SATURDAY); // 2
	player->addAttendance(SUNDAY); // 2
	policy->apply(*player);
	EXPECT_EQ(player->getPoints(), 1 + 1 + 3 + 1 + 1 + 2 + 2); // Total points should be 11
}

TEST_F(PolicyFixture, BonusApplyTestWednesdayCase) {
	setPolicy(new BonusPointPolicy());
	// Simulate attendance
	player->addAttendance(WEDNESDAY); // 10 times
	for (int i = 0; i < 10; ++i) {
		player->addAttendance(WEDNESDAY);
	}
	policy->apply(*player);
	EXPECT_EQ(player->getPoints(), 10);
}

TEST_F(PolicyFixture, BonusApplyTestWeekendCase) {
	setPolicy(new BonusPointPolicy());

	player->addAttendance(SATURDAY); // 5 times
	for (int i = 0; i < 5; ++i) {
		player->addAttendance(SATURDAY);
	}
	player->addAttendance(SUNDAY); // 5 times
	for (int i = 0; i < 5; ++i) {
		player->addAttendance(SUNDAY);
	}
	policy->apply(*player);
	EXPECT_EQ(player->getPoints(), 10);
}

TEST_F(PolicyFixture, GradeApplyTest) {
	setPolicy(new GradePolicy());
	player->addPoints(10);
	policy->apply(*player);
	EXPECT_EQ(player->getGradeName(), "NORMAL");
	player->addPoints(20);
	policy->apply(*player);
	EXPECT_EQ(player->getGradeName(), "SILVER");
	player->addPoints(30);
	policy->apply(*player);
	EXPECT_EQ(player->getGradeName(), "GOLD");
}
