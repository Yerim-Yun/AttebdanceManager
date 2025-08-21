#include "grade.h"
#include "gmock/gmock.h"

class GradeFixture : public ::testing::Test {
public:
	IGrade *grade;
};

TEST(GradeTest, NormalGradeTest) {
	IGrade *grade = new NormalGrade();
	EXPECT_EQ(grade->getGradeName(), "NORMAL");
}

TEST(GradeTest, SilverGradeTest) {
	IGrade* grade = new SilverGrade();
	EXPECT_EQ(grade->getGradeName(), "SILVER");
}

TEST(GradeTest, GoldGradeTest) {
	IGrade* grade = new GoldGrade();
	EXPECT_EQ(grade->getGradeName(), "GOLD");
}

