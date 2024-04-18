#include <gtest/gtest.h>
#include "System.h"
#include "utils.h"

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
//    EXPECT_TRUE(system->getFirstDevice() == NULL);
//    EXPECT_TRUE(system->getFirstJob() == NULL);
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

TEST_F(TestSystem, ReadData_PageCount_NaN) {
    EXPECT_TRUE(system->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getFirstJob() == NULL);
    system->ReadData("xml_tests/PageCountNaN.xml");
    EXPECT_TRUE(system->getDevices().size() == 1);
    EXPECT_TRUE(system->getJobs().size() == 1);
}
//////////////////////////////////////////////////////////////////
///                         REPORTS                            ///
//////////////////////////////////////////////////////////////////
TEST_F(TestSystem, printReportHD){
    system->ReadData("xml_tests/ReportHD.xml");
    system->getDevices()[0]->addJob(system->getJobs()[0]);
    system->getDevices()[1]->addJob(system->getJobs()[1]);
    system->getDevices()[2]->addJob(system->getJobs()[2]);
    system->getDevices()[0]->addJob(system->getJobs()[3]);
    system->getDevices()[1]->addJob(system->getJobs()[4]);
    system->getDevices()[2]->addJob(system->getJobs()[5]);
    system->getDevices()[0]->addJob(system->getJobs()[6]);

    std::string filename = system->printReport();
    EXPECT_TRUE(FileCompare(filename, "report_tests/ReportHD.txt"));
}

TEST_F(TestSystem, printEmpty){
    std::string filename = system->printReport();
    EXPECT_TRUE(FileCompare(filename, "report_tests/ReportEMPTY.txt"));
}



//////////////////////////////////////////////////////////////////
///                         INCONSISTENCY TEST                 ///
//////////////////////////////////////////////////////////////////

TEST_F(TestSystem, Inconsistency_Neg_Num1){
    system->ReadData("xml_tests/Neg_Num.xml");
    EXPECT_FALSE(system->VerifyConsistency());
}

TEST_F(TestSystem, Inconsistency_Neg_Num2){
    system->ReadData("xml_tests/Neg_Num.xml");
    EXPECT_FALSE(system->VerifyConsistency());
}



TEST_F(TestSystem, Inconsistency_Job_Num){
    system->ReadData("xml_tests/Job_Num.xml");
    EXPECT_FALSE(system->VerifyConsistency());
}


//////////////////////////////////////////////////////////////////
/// Manual Processing
//////////////////////////////////////////////////////////////////
TEST_F(TestSystem, Manual_Processing_Forget_Device){
	system->ReadData("xml_tests/ManualProcessing.xml");
	EXPECT_TRUE(!system->getJobs().empty());
	EXPECT_TRUE(!system->getDevices().empty());
	// Oopsie we forgot to add the devices to the system
	// system->assignAllJobs();

	// throws an assertion error, because we forgot to assign the jobs to the devices first
	EXPECT_DEATH(system->processFirstJob(), ".*Job is not assigned to a device.*");
}

TEST_F(TestSystem, Manual_Processing_HappyDay){
	system->ReadData("xml_tests/ManualProcessing.xml");
	EXPECT_TRUE(!system->getJobs().empty());
	EXPECT_TRUE(!system->getDevices().empty());

	// assign the jobs to the devices
	system->assignAllJobs();
	// generate the log filename
	std::string log_file = GenerateFileName("logs/log-", LOG_FILE_EXTENSION);
	// enable logging
	system->setLogMessages(true);
	system->setLogFile(log_file);
	// process the first job
	EXPECT_NO_FATAL_FAILURE(system->processFirstJob());
	// compare the log file with the expected log file
	EXPECT_TRUE(FileExists(log_file));
	EXPECT_TRUE(FileCompare(log_file, "log_tests/ManualProcessing.log"));
}

//////////////////////////////////////////////////////////////////
///                  Automatic Processing                      ///
//////////////////////////////////////////////////////////////////


TEST_F(TestSystem, AP_HappyDay){
    // generate the log filename
    std::string log_file = GenerateFileName("logs/log-", LOG_FILE_EXTENSION);
    // enable logging
    system->setLogMessages(true);
    system->setLogFile(log_file);

    system->ReadData("xml_tests/ReportHD.xml");
    system->processAll();

    EXPECT_TRUE(FileCompare(log_file, "log_tests/AP_HappyDay.txt"));
}

TEST_F(TestSystem, EmptySys){
  EXPECT_DEATH(system->processAll(), ".*No jobs were found.*");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // to allow for threadsafe death tests
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}