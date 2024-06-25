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

class TestSystemTracker : public ::testing::Test {
protected:
    SystemTracker *tracker{};

    void SetUp() {
        tracker = new SystemTracker();
    }

    void TearDown() {
        delete tracker;
        tracker = nullptr;
    }
};

class TestLogger : public ::testing::Test {
protected:
    std::string output;
    Logger *logger;

    void SetUp() {
        logger = new Logger();
    }

    void TearDown() {
        delete logger;
        logger = nullptr;
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

    EXPECT_TRUE(StringCompare(output, "ERROR: No name is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}


TEST_F(TestUseCase1o1, ReadData_NoEmission) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoEmission.xml");

    EXPECT_TRUE(StringCompare(output, "ERROR: No emission is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}

TEST_F(TestUseCase1o1, ReadData_Emission_NaN) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/EmissionNaN.xml");

    EXPECT_TRUE(StringCompare(output, "ERROR: Emission should be an integer number\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}

TEST_F(TestUseCase1o1, ReadData_NoSpeed) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoSpeed.xml");

    EXPECT_TRUE(StringCompare(output, "ERROR: No speed is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().empty());
    EXPECT_TRUE(system->getManager()->getJobs().size() == 2);
}

TEST_F(TestUseCase1o1, ReadData_SpeedNaN) {
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


TEST_F(TestUseCase1o1, ReadData_NoPageCount) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoPageCount.xml");

    EXPECT_TRUE(StringCompare(output, "ERROR: No page count is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().size() == 1);
    EXPECT_TRUE(system->getManager()->getJobs().size() == 1);
}

TEST_F(TestUseCase1o1, ReadData_NoUsername) {
    EXPECT_TRUE(system->getManager()->getFirstDevice() == NULL);
    EXPECT_TRUE(system->getManager()->getFirstJob() == NULL);
    system->ReadData("xml_tests/NoUsername.xml");

    EXPECT_TRUE(StringCompare(output, "ERROR: No user name is provided\n"));
    EXPECT_TRUE(system->getManager()->getDevices().size() == 1);
    EXPECT_TRUE(system->getManager()->getJobs().size() == 1);
}

TEST_F(TestUseCase1o1, ReadData_JobNumber_NaN) {
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
TEST_F(TestSystem, printReportHD) {
    system->ReadData("xml_tests/ReportHD.xml");
    system->processAll();

    std::string filename = GenerateFileName("reports/report-", REPORT_FILE_EXTENSION);
    Reporter reporter;
    system->printReport(&reporter);
    reporter.toFile(filename);
    EXPECT_TRUE(FileCompare(filename, "report_tests/ReportHD.txt"));
}

TEST_F(TestSystem, printEmpty) {
    std::string filename = GenerateFileName("reports/report-", REPORT_FILE_EXTENSION);
    Reporter reporter;
    system->printReport(&reporter);
    reporter.toFile(filename);
    EXPECT_TRUE(FileCompare(filename, "report_tests/ReportEMPTY.txt"));
}

TEST_F(TestSystem, PartialProcessing) {
    system->ReadData("xml_tests/ReportHD.xml");
    system->getAssigner()->assignAllJobs();
    system->getManager()->getDevices()[0]->processJob();

    std::string filename = GenerateFileName("reports/report-", REPORT_FILE_EXTENSION);
    Reporter reporter;
    system->printReport(&reporter);
    reporter.toFile(filename);
    EXPECT_TRUE(FileCompare(filename, "report_tests/PartialProcessing.txt"));
}

TEST_F(TestSystem, AdvancedTextualOutput) {
    system->ReadData("xml_tests/ReportHD.xml");
    system->getAssigner()->assignAllJobs();

    std::string filename = GenerateFileName("reports/report-", REPORT_FILE_EXTENSION);
    Reporter reporter;
    system->AdvancePrintReport(&reporter);
    reporter.toFile(filename);
    EXPECT_TRUE(FileCompare(filename, "report_tests/AdvancedReport.txt"));
}


//////////////////////////////////////////////////////////////////
///                         INCONSISTENCY TEST                 ///
//////////////////////////////////////////////////////////////////


TEST_F(TestSystem, Inconsistency_Neg_Num_Job) {
    std::string log_file = GenerateFileName("logs/log-", LOG_FILE_EXTENSION);
    FileLogger *logger = new FileLogger(log_file);
    system->setLogger(logger);
    system->ReadData("xml_tests/Neg_Num.xml");
    EXPECT_TRUE(FileCompare(log_file, "consistency_tests/Neg_Num.txt"));
}


TEST_F(TestSystem, Inconsistency_Job_Num) {
    system->ReadData("xml_tests/Job_Num.xml");
    EXPECT_FALSE(system->VerifyConsistency());
}


//////////////////////////////////////////////////////////////////
/// Manual Processing
//////////////////////////////////////////////////////////////////
TEST_F(TestSystem, Manual_Processing_Forget_Device) {
    system->ReadData("xml_tests/ManualProcessing.xml");
    EXPECT_TRUE(!system->getManager()->getJobs().empty());
    EXPECT_TRUE(!system->getManager()->getDevices().empty());
    // Oopsie we forgot to add the devices to the system
    // system->assignAllJobs();

    // throws an assertion error, because we forgot to assign the jobs to the devices first
    EXPECT_DEATH(system->processFirstJob(), ".*All jobs are processed.*");
}

TEST_F(TestSystem, Manual_Processing_HappyDay) {
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


TEST_F(TestSystem, AP_HappyDay) {
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

TEST_F(TestSystem, EmptySys) {
    EXPECT_DEATH(system->processAll(), ".*No jobs were found.*");
}


//////////////////////////////////////////////////////////////////
///                  Tracking CO2 emissions                    ///
//////////////////////////////////////////////////////////////////

TEST_F(TestSystem, CO2_HappyDay) {
    system->ReadData("xml_tests/Track_CO2.xml");
    system->processAll();
    SystemTracker *tracker = system->getTracker();

    EXPECT_EQ(tracker->getCo2Emission(), 105);

}

TEST_F(TestSystem, CO2_Empty) {
    system->ReadData("xml_tests/Track_CO2_MT.xml");
    SystemTracker *tracker = system->getTracker();

    EXPECT_EQ(tracker->getCo2Emission(), 0);

}

//////////////////////////////////////////////////////////////////
///                  Testing System Tracker                    ///
//////////////////////////////////////////////////////////////////

TEST_F(TestSystemTracker, CO2_Emptyy) {
    EXPECT_EQ(tracker->getCo2Emission(), 0);
}

TEST_F(TestSystemTracker, CO2_Add) {
    tracker->addCo2Emission(10);
    EXPECT_EQ(tracker->getCo2Emission(), 10);
}

TEST_F(TestSystemTracker, CO2_Add_Neg) {
    EXPECT_DEATH(tracker->addCo2Emission(-10), ".*CO2 emission cannot be negative.*");
}

TEST_F(TestSystemTracker, CO2_Neg_Page) {
    EXPECT_DEATH(tracker->addPages(-10), ".*Total pages cannot be negative.*");
}

//////////////////////////////////////////////////////////////////
///                  Testing System FileLogger                    ///
//////////////////////////////////////////////////////////////////

TEST_F(TestLogger, TestFileLogger) {
    std::string log_file = GenerateFileName("logs/log-", LOG_FILE_EXTENSION);
    delete logger;
    logger = nullptr;
    logger = new FileLogger(log_file);
    std::string lorem = "Lorem ipsum dolor sit amet. At dignissimos iure in alias culpa ab corrupti rerum vel nulla tempore est mollitia voluptate vel inventore galisum. Sed autem voluptatem et dicta nobis sit velit officia qui dolore similique.\n"
                        "Eos dignissimos cupiditate sed sequi molestias ab aperiam voluptatem ut consequatur fugiat vel galisum porro et maiores eligendi. Id vero consequatur ea inventore dicta aut nemo consequatur vel sint nulla aut possimus omnis.\n"
                        "Et veritatis earum et inventore enim a corrupti consectetur At incidunt dolore est pariatur omnis. Vel fugit ipsa est atque ipsa ea impedit iste in modi mollitia. Est quidem esse a voluptas dolorum a laborum quisquam et exercitationem tempora et dolor internos non quibusdam culpa et quidem sint. Sed repellendus voluptatem ut reiciendis voluptates rem ratione dolorum?";

    logger->log(lorem);
    EXPECT_TRUE(FileCompare(log_file, "log_tests/FileLoggerTest.log"));
}

TEST_F(TestLogger, TestFileErrorLogger) {
    std::string log_file = GenerateFileName("logs/log-", LOG_FILE_EXTENSION);
    delete logger;
    logger = nullptr;
    logger = new FileLogger(log_file);
    std::string lorem = "Lorem ipsum dolor sit amet. At dignissimos iure in alias culpa ab corrupti rerum vel nulla tempore est mollitia voluptate vel inventore galisum. Sed autem voluptatem et dicta nobis sit velit officia qui dolore similique.\n"
                        "Eos dignissimos cupiditate sed sequi molestias ab aperiam voluptatem ut consequatur fugiat vel galisum porro et maiores eligendi. Id vero consequatur ea inventore dicta aut nemo consequatur vel sint nulla aut possimus omnis.\n"
                        "Et veritatis earum et inventore enim a corrupti consectetur At incidunt dolore est pariatur omnis. Vel fugit ipsa est atque ipsa ea impedit iste in modi mollitia. Est quidem esse a voluptas dolorum a laborum quisquam et exercitationem tempora et dolor internos non quibusdam culpa et quidem sint. Sed repellendus voluptatem ut reiciendis voluptates rem ratione dolorum?";

    logger->error(lorem);
    EXPECT_TRUE(FileCompare(log_file, "log_tests/FileErrorLoggerTest.log"));
}

TEST_F(TestLogger, TestStringLogger) {
    delete logger;
    logger = nullptr;
    logger = new StringLogger(&output);

    std::string lorem = "lorem ipsum dolor sit amet. at dignissimos iure in alias culpa ab corrupti rerum vel nulla tempore est mollitia voluptate vel inventore galisum. sed autem voluptatem et dicta nobis sit velit officia qui dolore similique.\n"
                        "eos dignissimos cupiditate sed sequi molestias ab aperiam voluptatem ut consequatur fugiat vel galisum porro et maiores eligendi. id vero consequatur ea inventore dicta aut nemo consequatur vel sint nulla aut possimus omnis.\n"
                        "et veritatis earum et inventore enim a corrupti consectetur at incidunt dolore est pariatur omnis. vel fugit ipsa est atque ipsa ea impedit iste in modi mollitia. est quidem esse a voluptas dolorum a laborum quisquam et exercitationem tempora et dolor internos non quibusdam culpa et quidem sint. sed repellendus voluptatem ut reiciendis voluptates rem ratione dolorum?";

    logger->log(lorem);
    lorem += "\n";
    EXPECT_TRUE(output == lorem);
}

TEST_F(TestLogger, TestStringErrorLogger) {
    delete logger;
    logger = nullptr;
    logger = new StringLogger(&output);

    std::string lorem = "lorem ipsum dolor sit amet. at dignissimos iure in alias culpa ab corrupti rerum vel nulla tempore est mollitia voluptate vel inventore galisum. sed autem voluptatem et dicta nobis sit velit officia qui dolore similique.\n"
                        "eos dignissimos cupiditate sed sequi molestias ab aperiam voluptatem ut consequatur fugiat vel galisum porro et maiores eligendi. id vero consequatur ea inventore dicta aut nemo consequatur vel sint nulla aut possimus omnis.\n"
                        "et veritatis earum et inventore enim a corrupti consectetur at incidunt dolore est pariatur omnis. vel fugit ipsa est atque ipsa ea impedit iste in modi mollitia. est quidem esse a voluptas dolorum a laborum quisquam et exercitationem tempora et dolor internos non quibusdam culpa et quidem sint. sed repellendus voluptatem ut reiciendis voluptates rem ratione dolorum?";

    logger->error(lorem);
    lorem += "\n";
    lorem = "ERROR: " + lorem;
    EXPECT_TRUE(output == lorem);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // to allow for threadsafe death tests
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}
