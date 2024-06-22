//
// Created by student on 29/02/24.
//
#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "System.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "SystemReader.h"
#include "Reporter.h"

System::System() {
    _init = this;
    manager = new SystemManager();
    logger = new Logger();
    reader = new SystemReader(manager, logger);
    assigner = new SystemAssigner(manager, logger);
    tracker = new SystemTracker();
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
    REQUIRE(properlyInitialized(), "System is not properly initialized");

    return manager;
}

Logger *System::getLogger() const {
    REQUIRE(properlyInitialized(), "System is not properly initialized");

    return logger;
}

SystemReader *System::getReader() const {
    REQUIRE(properlyInitialized(), "System is not properly initialized");

    return reader;
}

SystemAssigner *System::getAssigner() const {
    REQUIRE(properlyInitialized(), "System is not properly initialized");

    return assigner;
}

SystemTracker *System::getTracker() const {
    REQUIRE(properlyInitialized(), "System is not properly initialized");

    return tracker;
}

void System::ReadData(const std::string &file_name) {
    REQUIRE(properlyInitialized(), "System is not properly initialized.");
    REQUIRE(FileExists(file_name), "File does not exist.");

	reader->ReadData(file_name);

    VerifyConsistency();
}

void System::clear() {
    REQUIRE(properlyInitialized(), "System is not properly initialized");

    delete manager;
    manager = new SystemManager();
}

void System::printReport(Reporter *reporter) const {
	REQUIRE(properlyInitialized(), "System is not properly initialized");
	REQUIRE(VerifyConsistency(), "Printing system is inconsistent");
    REQUIRE(properlyInitialized(), "System is not properly initialised");

    reporter->generateSystemStatus(manager->getDevices(), manager->getJobs());
}

bool System::VerifyConsistency() const {
    REQUIRE(properlyInitialized(),  "System is not properly initialized.");

    std::vector<int> job_nums{};
    ///Check if PageCount and JobNumber are not negative
    for(Job *const& job : manager->getJobs()){
        if(job->getPageCount() < 0){
            logger->error("Page count is negative");
            return false;
        }
        else if(job->getJobNumber() < 0) {
			logger->error("Job number is negative");
            return false;
        }

        if(std::find(job_nums.begin(), job_nums.end(),job->getJobNumber()) != job_nums.end()){
            logger->error("Duplicate job number found");
            return false;
        }
        else{
            job_nums.push_back(job->getJobNumber());
        }
    }

    ///Check if Emission and Speed are not negative
    for (Device *const &device : manager->getDevices()){
        if(device->getEmission() < 0){
            logger->error("Emission is negative");
            return false;
        }
        else if(device->getSpeed() < 0){
            logger->error("Speed is negative");
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
        if (wait_for_print) {
            std::chrono::milliseconds duration(60 / device->getSpeed() * 1000);
            std::this_thread::sleep_for(duration);
        }
    } while (job->getStatus() != Job::done);

	logger->log(message);

	ENSURE(job->getStatus() == Job::done, "Job is not finished");
	ENSURE(job->getAssignedTo()->getLoad() != initialLoad, "Device did not process the job");

    tracker->addPages(job->getPageCount());
    tracker->addCo2Emission(job->getPageCount() * device->getEmission());

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

void System::AdvancePrintReport(Reporter *reporter) {
    REQUIRE(properlyInitialized(), "System is not properly initialized");
    REQUIRE(VerifyConsistency(), "Printing system is inconsistent");

    for(Device *device : manager->getDevices()){
        reporter->generateDeviceAdvancedReport(device);
    }
}
