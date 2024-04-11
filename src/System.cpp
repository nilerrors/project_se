//
// Created by student on 29/02/24.
//
#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "System.h"
#include <iostream>
#include <fstream>
#include "SystemReader.h"

System::System() {
    _init = this;
    manager = new SystemManager();
    logger = new Logger();
    reader = new SystemReader(manager, logger);
    assigner = new SystemAssigner(manager, logger);
}

System::~System() {
    _init = NULL;
    delete manager;
    delete reader;
    delete assigner;
    manager = NULL;
    reader = NULL;
    assigner = NULL;
}

SystemManager *System::getManager() const {
    REQUIRE(properlyInitialized(), "Class is not properly initialized");
    return manager;
}

Logger *System::getLogger() const {
    return logger;
}

SystemReader *System::getReader() const {
    return reader;
}

SystemAssigner *System::getAssigner() const {
    return assigner;
}

void System::ReadData(const std::string &file_name) {
    REQUIRE(properlyInitialized(), "Class is not properly initialized.");
    REQUIRE(FileExists(file_name), "File does not exist.");

	reader->ReadData(file_name);

    VerifyConsistency();
}

void System::clear() {
    delete manager;
    manager = new SystemManager();
}

std::string System::printReport() const {
    /*
    Prints a report of the system
     */
	REQUIRE(properlyInitialized(), "Class is not properly initialized");
	REQUIRE(VerifyConsistency(), "Printing system is inconsistent");

    std::string filename = GenerateFileName("reports/report-", REPORT_FILE_EXTENSION);
    std::ofstream report;
    report.open(filename);

    report << "# === [System Status] === #" << std::endl << std::endl;
    report << "--== Devices ==--" << std::endl << std::endl;

    for(Device *device : manager->getDevices()) {
        report << device->printReport();
        if (device != manager->getDevices().back())
            report << "\n\n";
    }

    report << std::endl << "--== Jobs ==--" << std::endl << std::endl;
    for(Job *job : manager->getJobs()) {
        report << job->printReport();
        if (job != manager->getJobs().back())
            report << "\n\n";
    }

    report << "\n\n";
    report<<"# ======================= #"<<std::endl;

    report.close();
    return filename;
}

bool System::VerifyConsistency() const {
    REQUIRE(properlyInitialized(),  "Class is not properly initialized.");

    std::vector<int> job_nums{};
    ///Check if PageCount and JobNumber are not negative
    for(Job *const& job : manager->getJobs()){
        if(job->getPageCount() < 0 || job->getJobNumber() < 0) {
			logger->error("Inconsistent printing system");
            return false;
        }

        if(std::find(job_nums.begin(), job_nums.end(),job->getJobNumber()) != job_nums.end()){
            logger->error("Inconsistent printing system");
            return false;
        }
        else{
            job_nums.push_back(job->getJobNumber());
        }
    }

    ///Check if Emission and Speed are not negative
    for (Device *const &device : manager->getDevices()){
        if(device->getEmission() < 0 || device->getSpeed() < 0) {
            logger->error("Inconsistent printing system");
			return false;
        }
    }

    return true;
}

void System::processFirstJob() const {
	REQUIRE(properlyInitialized(), "System is not properly initialized.");
	REQUIRE(!manager->getJobs().empty(), "No jobs were found");
	REQUIRE(!manager->getDevices().empty(), "No devices were found");
	REQUIRE(manager->getFirstUnprocessedJob() != NULL, "All jobs are processed");
	REQUIRE(manager->getFirstUnprocessedJob()->getAssignedTo() != NULL, "Job is not assigned to a device");

	Job *job = manager->getFirstUnprocessedJob();
	Device *device = job->getAssignedTo();
	int initialLoad = device->getLoad();
    job->setStatus(Job::waiting);
    std::string message;

    // print all pages
    do {
        message = device->processJob();
    } while (job->getStatus() != Job::done);

	logger->log(message);

	ENSURE(job->getStatus() == Job::done, "Job is not finished");
	ENSURE(job->getAssignedTo()->getLoad() != initialLoad, "Device did not process the job");
}

void System::processAll() {
    /*
    Automatically assigns all jobs to printers and processes all unfinished jobs.
    Precon: Systems is properly loaded
    Postcon: All pages have been printed i.e. all jobs are finished
    */
    REQUIRE(properlyInitialized(), "System is not properly initialized");
    assigner->assignAllJobs();
    while(manager->getFirstUnprocessedJob() != NULL){
        processFirstJob();
    }
    ENSURE(manager->getFirstUnprocessedJob() == NULL, "Not all pages were printed");
}

void System::setLogger(Logger *log)
{
	REQUIRE(properlyInitialized(), "System is not properly initialized");
	REQUIRE(log != NULL, "Logger is a NULL pointer");
    delete logger;
	logger = log;
    assigner->setLogger(logger);
    reader->setLogger(logger);
	ENSURE(logger == log, "Logger was not set");
}

std::string System::AdvancePrintReport() {
    REQUIRE(properlyInitialized(), "Class is not properly initialized");
    REQUIRE(VerifyConsistency(), "Printing system is inconsistent");

    std::string filename = GenerateFileName("reports/report-", REPORT_FILE_EXTENSION);
    std::ofstream report;
    report.open(filename);

    for(Device *device : manager->getDevices()){
        report << device->AdvancePrintReport();
    }
    report.close();
    return filename;
}
