#include <gtest/gtest.h>
#include "System.h"

class TestSystem : public ::testing::Test {
protected:
	System *system;

	void SetUp() override {
		system = new System();
	}

	void TearDown() override {
		delete system;
	}
};

TEST_F(TestSystem, ReadData) {
	EXPECT_TRUE(system->properlyInitialized());
	EXP(system->ReadData("xml_tests/NoName.xml"), "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
