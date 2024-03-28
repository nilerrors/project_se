#include <gtest/gtest.h>
#include "System.h"
#include "lib/utils.h"

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

class TestUseCase1o1 : public TestSystem {
protected:
	std::string output;
	StringLogger *logger{};

	void SetUp() override {
		TestSystem::SetUp();
		logger = new StringLogger(&output);
		system->setLogger(logger);
	}

	void TearDown() override {
		delete logger;
		logger = nullptr;
		TestSystem::TearDown();
	}
};

//////////////////////////////////////////////////////////////////
/// DEVICES
//////////////////////////////////////////////////////////////////
TEST_F(TestUseCase1o1, ReadData_NoName) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);

	system->ReadData("xml_tests/NoName.xml");
    std::cout<<output<<std::endl;
	EXPECT_TRUE(StringCompare(output, "ERROR: No name is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}


TEST_F(TestUseCase1o1, ReadData_NoEmission){
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoEmission.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: No emission is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}

TEST_F(TestUseCase1o1, ReadData_Emission_NaN){
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/EmissionNaN.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: Emission should be an integer number\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}

TEST_F(TestUseCase1o1, ReadData_NoSpeed){
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoSpeed.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: No speed is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}

TEST_F(TestUseCase1o1, ReadData_SpeedNaN){
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/SpeedNaN.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: Speed should be an integer number\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}

//////////////////////////////////////////////////////////////////
/// JOBS
//////////////////////////////////////////////////////////////////
TEST_F(TestUseCase1o1, ReadData_NoJobNumber) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoJobNumber.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: No job number is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().size() == 1);
    EXPECT_TRUE(system->getManager()->getJobs().size() == 1);
}


TEST_F(TestUseCase1o1, ReadData_NoPageCount){
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoPageCount.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: No page count is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().size() == 1);
    EXPECT_TRUE(system->getManager()->getJobs().size() == 1);
}

TEST_F(TestUseCase1o1, ReadData_NoUsername){
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoUsername.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: No user name is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().size() == 1);
    EXPECT_TRUE(system->getManager()->getJobs().size() == 1);
}

TEST_F(TestUseCase1o1, ReadData_JobNumber_NaN){
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/JobNumberNaN.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: Job number should be a number\n"));
    EXPECT_TRUE(system->getManager()->getDevices().size() == 1);
    EXPECT_TRUE(system->getManager()->getJobs().size() == 1);
}

TEST_F(TestUseCase1o1, ReadData_PageCount_NaN) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/PageCountNaN.xml");

	EXPECT_TRUE(StringCompare(output, "ERROR: Page count should be a number\n"));
    EXPECT_TRUE(system->getManager()->getDevices().size() == 1);
    EXPECT_TRUE(system->getManager()->getJobs().size() == 1);
}


//////////////////////////////////////////////////////////////////
///                         REPORTS                            ///
//////////////////////////////////////////////////////////////////
TEST_F(TestSystem, printReportHD){
    system->ReadData("xml_tests/ReportHD.xml");
    system->getManager()->getDevices()[0]->addJob(system->getManager()->getJobs()[0]);
    system->getManager()->getDevices()[1]->addJob(system->getManager()->getJobs()[1]);
    system->getManager()->getDevices()[2]->addJob(system->getManager()->getJobs()[2]);
    system->getManager()->getDevices()[0]->addJob(system->getManager()->getJobs()[3]);
    system->getManager()->getDevices()[1]->addJob(system->getManager()->getJobs()[4]);
    system->getManager()->getDevices()[2]->addJob(system->getManager()->getJobs()[5]);
    system->getManager()->getDevices()[0]->addJob(system->getManager()->getJobs()[6]);

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
	EXPECT_TRUE(!system->getManager()->getJobs().empty());
	EXPECT_TRUE(!system->getManager()->getDevices().empty());
	// Oopsie we forgot to add the devices to the system
	// system->assignAllJobs();

	// throws an assertion error, because we forgot to assign the jobs to the devices first
	EXPECT_DEATH(system->processFirstJob(), ".*Job is not assigned to a device.*");
}

TEST_F(TestSystem, Manual_Processing_HappyDay){
	system->ReadData("xml_tests/ManualProcessing.xml");
	EXPECT_TRUE(!system->getManager()->getJobs().empty());
	EXPECT_TRUE(!system->getManager()->getDevices().empty());

	// assign the jobs to the devices
	system->getAssigner()->assignAllJobs();
	// generate the log filename
	std::string log_file = GenerateFileName("logs/log-", LOG_FILE_EXTENSION);
	FileLogger *logger = new FileLogger(log_file);
	// enable logging
	system->setLogger(logger);
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
	FileLogger *logger = new FileLogger(log_file);
	// enable logging
	system->setLogger(logger);

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