//
// Created by student on 29/02/24.
//

#include "DesignByContract.h"
#include "utils.h"
#include "System.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <random>
#include "utils.h"

System::System() {
    _init = this;
	log_errors = false;
}

System::~System() {
    for(Device*& device: devices){
        delete device;
    }
    for(Job*& job : jobs){
        delete job;
    }
    devices.clear();
    jobs.clear();
    _init = NULL;
    this->clear();
}

void System::ReadData(const std::string &file_name) {
    REQUIRE(properlyInitialized(), "Class is not properly initialized.");
    REQUIRE(FileExists(file_name), "File does not exist.");

    TiXmlDocument doc;
    if (!doc.LoadFile(file_name.c_str())) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to read the file: No SYSTEM root." << std::endl;
        return;
    }
    if (std::string(root->Value()) != "SYSTEM")
    {
        std::cerr << "Failed to read the file: Unexpected root '"
                    << root->Value() << "', Expected 'SYSTEM'." << std::endl;
    }

    for (TiXmlElement *elm = root->FirstChildElement(); elm != NULL; elm = elm->NextSiblingElement())
    {
        if (std::string(elm->Value()) == "DEVICE") {
            ReadDevice(elm);
        } else if (std::string(elm->Value()) == "JOB") {
            ReadJob(elm);
        }
        else{
            std::cerr << "Unrecognizable element"<<std::endl;
            continue;
        }
    }

    VerifyConsistency();
    doc.Clear();
}

void System::ReadDevice(TiXmlElement *device_element) {
    REQUIRE(device_element!= NULL, "device_element is a NULL pointer");
    try {
        Device* device = new Device(device_element);
        devices.push_back(device);

        ENSURE(!devices.empty(), "No devices were read after reading xml file");
    }
    catch (const std::runtime_error& error) {
        if (!log_errors)
            return;
        std::cerr << error.what() << std::endl;
    }
}

void System::ReadJob(TiXmlElement *job_element) {
    REQUIRE(job_element!= NULL, "job_element is a NULL pointer");
    try {
        Job* job = new Job(job_element);
        jobs.push_back(job);

        ENSURE(!jobs.empty(), "No Jobs were read after reading xml file");
    }
    catch (const std::runtime_error& error) {
        if (!log_errors)
            return;
        std::cerr << error.what() << std::endl;
    }
}


Device *System::getFirstDevice() const {
	REQUIRE(properlyInitialized(), "Class is not properly initialized");
    return devices.empty() ? nullptr : devices.front();
}

Job *System::getFirstJob() const {
	REQUIRE(properlyInitialized(), "Class is not properly initialized");
    return jobs.empty() ? nullptr : jobs.front();
}

Job *System::getFirstUnfinishedJob() const {
	for(Job *job : jobs){
		if(!job->isFinished()) {
			return job;
		}
	}
	return NULL;
}

const std::vector<Device *> &System::getDevices() const {
    return devices;
}

const std::vector<Job *> &System::getJobs() const {
    return jobs;
}

std::vector<Job *> System::getUnfinishedJobs() const {
	std::vector<Job *> unfinished_jobs;
	for(Job *job : jobs){
		if(!job->isFinished()) {
			unfinished_jobs.push_back(job);
		}
	}
	return unfinished_jobs;
}

void System::clear() {
    for (Device *&device: devices) {
        delete device;
        device = NULL;
    }
    for (Job *&job: jobs) {
        delete job;
        job = NULL;
    }
}

std::string System::printReport() const {
    /*
     Generate a .txt file detailing the contents of the system. The file will contain information about all printers and jobs of the system respectively.
     return: Filename van de report
     */
	REQUIRE(properlyInitialized(), "Class is not properly initialized");
	REQUIRE(VerifyConsistency(), "Printing system is inconsistent");

    std::string filename = GenerateFileName("reports/report-", REPORT_FILE_EXTENSION);
    std::ofstream report;
    report.open(filename);
    for(Device *device : devices) {
        report << device->printReport();
        if (device != devices.back())
            report << "\n\n";
    }
    report.close();
    return filename;
}

bool System::VerifyConsistency() const {
    REQUIRE(properlyInitialized(),  "Class is not properly initialized.");

    std::vector<int> job_nums{};
    ///Check if PageCount and JobNumber are not negative
    for(Job *const& job : jobs){
        if(!CheckNotNegative(job->getPageCount())){
            if (log_errors){
                std::cerr << "Inconsistent printing system" <<std::endl;
            }
            return false;
        }
        else if(!CheckNotNegative(job->getJobNumber())){
            if (log_errors){
                std::cerr << "Inconsistent printing system" <<std::endl;
            }
            return false;
        }

        if(std::find(job_nums.begin(), job_nums.end(),job->getJobNumber()) != job_nums.end()){
            if(log_errors)
                std::cerr << "Inconsistent printing system" <<std::endl;
            return false;
        }
        else{
            job_nums.push_back(job->getJobNumber());
        }
    }

    ///Check if Emission and Speed are not negative
    for(Device *const &device : devices){
        if(!CheckNotNegative(device->getEmission())){
            if(log_errors)
                std::cerr << "Inconsistent printing system" <<std::endl;
            return false;
        }
        else if(!CheckNotNegative(device->getSpeed())){
            if(log_errors){
                std::cerr << "Inconsistent printing system" <<std::endl;
            }
            return false;
        }
    }


    return true;
}

bool System::CheckNotNegative(int num) {
    return num*-1 < 0;
}

bool System::isLogErrors() const {
    return log_errors;
}

void System::setLogErrors(bool logErrors) {
    log_errors = logErrors;
}

Device *System::getDeviceWithLeastLoad() const {
	REQUIRE(properlyInitialized(), "System is not properly initialized.");
	REQUIRE(!devices.empty(), "No devices were found.");
	Device *least_loaded_device = devices.front();
	for(Device *device : devices){
		if(device->getLoad() < least_loaded_device->getLoad()){
			least_loaded_device = device;
		}
	}
	return least_loaded_device;
}

Job *System::getFirstUnprocessedJob() const
{
	REQUIRE(properlyInitialized(), "System is not properly initialized");
	REQUIRE(!jobs.empty(), "No jobs were found");
	for(Job *job : jobs){
		if(!job->isFinished() && !job->isInProcess()) {
			return job;
		}
	}
	return NULL;
}

Device *System::assignJobToDevice(Job *job) const {
	REQUIRE(properlyInitialized(), "System is not properly initialized");
	REQUIRE(!devices.empty(), "No devices were found");
	REQUIRE(job->getAssignedTo() == NULL, "Job is already assigned to a device.");

	Device *device = getDeviceWithLeastLoad();
	device->addJob(job);
	job->setAssignedTo(device);
	return device;
}

void System::assignAllJobs() const {
	REQUIRE(properlyInitialized(), "System is not properly initialized");
	REQUIRE(!jobs.empty(), "No jobs were found");
	REQUIRE(!devices.empty(), "No devices were found");

	for (Job *job : jobs)
	{
		if (job->getAssignedTo() == NULL)
		{
			assignJobToDevice(job);
		}
	}
}

void System::processFirstJob() const {
	REQUIRE(properlyInitialized(), "System is not properly initialized.");
	REQUIRE(!jobs.empty(), "No jobs were found");
	REQUIRE(!devices.empty(), "No devices were found");
	REQUIRE(getFirstUnprocessedJob() != NULL, "All jobs are processed");
	REQUIRE(getFirstUnprocessedJob()->getAssignedTo() != NULL, "Job is not assigned to a device");

	Job *job = getFirstUnprocessedJob();
	Device *device = job->getAssignedTo();
	int initialLoad = device->getLoad();
	job->setInProcess(true);
	std::string message = device->processJob();

	if (!log_file_name.empty() && log)
	{
		std::ofstream log_file(log_file_name, std::ios_base::app);
		log_file << message << std::endl;
		log_file.close();
	}
	else if (log)
	{
		std::cout << message << std::endl;
	}

	ENSURE(job->isFinished(), "Job is not finished");
	ENSURE(job->getAssignedTo()->getLoad() != initialLoad, "Device did not process the job");
}

void System::setLogFile(const std::string &log_file)
{
	REQUIRE(properlyInitialized(), "System is not properly initialized");
	log_file_name = log_file;
	ENSURE(log_file_name == log_file, "Log file is not set");
}

void System::setLogMessages(bool log_messages)
{
	REQUIRE(properlyInitialized(), "System is not properly initialized");
	log = log_messages;
	ENSURE(log == log_messages, "Log messages are not set");
}

void System::processAll() {
    /*
    Automatically assigns all jobs to printers and processes all unfinished jobs.
    Precon: Systems is properly loaded
    Postcon: All pages have been printed i.e. all jobs are finished
    */
    REQUIRE(properlyInitialized(), "System is not properly initialized");
    assignAllJobs();
    while(getFirstUnprocessedJob() != NULL){
        processFirstJob();
    }
    ENSURE(getFirstUnprocessedJob() == NULL, "Not all pages were printed");
}


