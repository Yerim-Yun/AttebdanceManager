#include "player.h"
#include "grade.h"
#include "policy.h"
#include "gmock/gmock.h"

using namespace testing;

class MockGrade : public IGrade {
public:
	MOCK_METHOD(string, getGradeName, (), (const, override));
	MOCK_METHOD(bool, isMeetCriteria, (int points), (const, override));
};

class PlayerFixture : public ::testing::Test {
public:
	void SetUp() override {
		player = new Player("Umar");
	}
	Player* player;
	
};

TEST_F(PlayerFixture, PlayerInitTest) {
	EXPECT_EQ(player->getName(), "Umar");
	EXPECT_EQ(player->getPoints(), 0);
	EXPECT_EQ(player->getGradeName(), "Unknown");
}

TEST_F(PlayerFixture, PlayerPointsTest) {
	player->addPoints(10);
	EXPECT_EQ(player->getPoints(), 10);
	player->addPoints(20);
	EXPECT_EQ(player->getPoints(), 30);
}

TEST_F(PlayerFixture, PlayerAttendanceTest) {
	player->addAttendance(MONDAY);
	EXPECT_EQ(player->getAttendanceCnt(MONDAY), 1);
	player->addAttendance(MONDAY);
	EXPECT_EQ(player->getAttendanceCnt(MONDAY), 2);
	player->addAttendance(TUESDAY);
	EXPECT_EQ(player->getAttendanceCnt(TUESDAY), 1);

	// not attended
	EXPECT_EQ(player->getAttendanceCnt(WEDNESDAY), 0);
}

TEST_F(PlayerFixture, PlayerGradeTest) {
	EXPECT_EQ(player->getGradeName(), "Unknown");

	auto mockGrade = std::make_unique<MockGrade>();
	EXPECT_CALL(*mockGrade, getGradeName())
		.WillRepeatedly(Return("TESTGRADE"));

	EXPECT_CALL(*mockGrade, isMeetCriteria(_))
		.WillRepeatedly(Return(true));

	player->setGrade(mockGrade.get());

	EXPECT_EQ(player->getGradeName(), "TESTGRADE");
	mockGrade = std::make_unique<MockGrade>();

}

TEST_F(PlayerFixture, PlayerGradeTestNotMeet) {
	auto mockGrade = std::make_unique<MockGrade>();
	EXPECT_CALL(*mockGrade, getGradeName())
		.WillRepeatedly(Return("TESTGRADE"));

	EXPECT_CALL(*mockGrade, isMeetCriteria(_))
		.WillRepeatedly(Return(false));

	std::vector<IGrade*> grades = { mockGrade.get() };
	GradePolicy policy(grades);

	policy.apply(*player);

	EXPECT_EQ(player->getGradeName(), "Unknown");
}