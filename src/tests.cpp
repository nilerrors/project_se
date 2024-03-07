#include <gtest/gtest.h>
#include "System.h"

class TestSystem : public ::testing::Test {
protected:
	System *system{};

	void SetUp() override {
		system = new System();
        system->setLogErrors(false);
	}

	void TearDown() override {
		delete system;
	}
};

//////////////////////////////////////////////////////////////////
/// DEVICES
//////////////////////////////////////////////////////////////////
TEST_F(TestSystem, ReadData_NoName) {
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
	system->ReadData("xml_tests/NoName.xml");
    EXPECT_TRUE(system->getDevices().empty());
    EXPECT_TRUE(system->getJobs().size() == 2);
}


TEST_F(TestSystem, ReadData_NoEmission){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoEmission.xml");
    EXPECT_TRUE(system->getDevices().empty());
    EXPECT_TRUE(system->getJobs().size() == 2);
}

TEST_F(TestSystem, ReadData_Emission_NaN){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/EmissionNaN.xml");
    EXPECT_TRUE(system->getDevices().empty());
    EXPECT_TRUE(system->getJobs().size() == 2);
}

TEST_F(TestSystem, ReadData_NoSpeed){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoSpeed.xml");
    EXPECT_TRUE(system->getDevices().empty());
    EXPECT_TRUE(system->getJobs().size() == 2);
}

TEST_F(TestSystem, ReadData_SpeedNaN){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/SpeedNaN.xml");
    EXPECT_TRUE(system->getDevices().empty());
    EXPECT_TRUE(system->getJobs().size() == 2);
}

//////////////////////////////////////////////////////////////////
/// JOBS
//////////////////////////////////////////////////////////////////
TEST_F(TestSystem, ReadData_NoJobNumber) {
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoJobNumber.xml");
    EXPECT_TRUE(system->getDevices().size() == 1);
    EXPECT_TRUE(system->getJobs().size() == 1);
}


TEST_F(TestSystem, ReadData_NoPageCount){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoPageCount.xml");
    EXPECT_TRUE(system->getDevices().size() == 1);
    EXPECT_TRUE(system->getJobs().size() == 1);
}

TEST_F(TestSystem, ReadData_NoUsername){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoUsername.xml");
    EXPECT_TRUE(system->getDevices().size() == 1);
    EXPECT_TRUE(system->getJobs().size() == 1);
}

TEST_F(TestSystem, ReadData_JobNumber_NaN){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/JobNumberNaN.xml");
    EXPECT_TRUE(system->getDevices().size() == 1);
    EXPECT_TRUE(system->getJobs().size() == 1);
}

TEST_F(TestSystem, ReadData_PageCount_NaN){
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/PageCountNaN.xml");
    EXPECT_TRUE(system->getDevices().size() == 1);
    EXPECT_TRUE(system->getJobs().size() == 1);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
