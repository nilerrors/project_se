#include <gtest/gtest.h>
#include "System.h"

class TestSystem : public ::testing::Test {
protected:
	System *system{};

	void SetUp() override {
		system = new System();
	}

	void TearDown() override {
		delete system;
	}
};

TEST_F(TestSystem, ReadData_NoName) {
	EXPECT_DEATH(system->ReadData("xml_tests/NoName.xml"),"");
}


TEST_F(TestSystem, ReadData_NoEmission){
    EXPECT_DEATH(system->ReadData("xml_tests/NoEmission.xml"), "");

}

TEST_F(TestSystem, ReadData_Emission_NaN){
    EXPECT_DEATH(system->ReadData("xml_tests/EmissionNaN.xml"), "");

}

TEST_F(TestSystem, ReadData_NoSpeed){
    EXPECT_DEATH(system->ReadData("xml_tests/NoSpeed.xml"), "");
}

TEST_F(TestSystem, ReadData_SpeedNaN){
    EXPECT_DEATH(system->ReadData("xml_tests/SpeedNaN.xml"), "");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
