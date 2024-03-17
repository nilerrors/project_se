//
// Created by student on 29/02/24.
//

#ifndef PRINTSYSTEM_SYSTEM_H
#define PRINTSYSTEM_SYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml.h"
#include "Device.h"
#include "Job.h"

static const std::string REPORT_FILE_EXTENSION = ".txt";
static const std::string LOG_FILE_EXTENSION = ".log";


class System
{
public:
	/**
	 * \brief Constructor for System
	 * \return A new System object
	 */
    System();

	/**
	 * \brief Destructor for System
	 */
    virtual ~System();

	/**
	 * \brief Clears the system
	 */
    void clear();

	/**
	 * \brief Reads the data from the file
	 * @param file_name

	 * @require
		- REQUIRE(properlyInitialized(), "Class is not properly initialized.");
		- REQUIRE(FileExists(file_name), "File does not exist.");
	 */
    void ReadData(const std::string &file_name);

	/**
	 * \brief Reads the device from the file
	 * @param device_element

	 * @require
	     - REQUIRE(device_element!= NULL, "device_element is a NULL pointer");

	 * @ensure
	 	 - ENSURE(!devices.empty(), "No devices were read after reading xml file");
	 */
    void ReadDevice(TiXmlElement *device_element);

	/**
	 * \brief Reads the job from the file
	 * @param job_element

	 * @require
	     - REQUIRE(job_element!= NULL, "job_element is a NULL pointer");

	 * @ensure
	 	 - ENSURE(!jobs.empty(), "No jobs were read after reading xml file");
	 */
    void ReadJob(TiXmlElement *job_element);

	/**
	 * \brief Checks if the class is properly
	 * @return A boolean indicating if the class is properly initialized
	 */
    bool properlyInitialized() const { return _init == this; }

	/**
	 * \brief Gets the first device
	 * @return

	 * @require
	  	- REQUIRE(properlyInitialized(), "Class is not properly initialized");
	 */
    Device *getFirstDevice() const;

	/**
	 * \brief Gets the first job
	 * @return

	 * @require
	  	- REQUIRE(properlyInitialized(), "Class is not properly initialized");
	 */
    Job *getFirstJob() const;

	/**
	 * \brief Gets the first unfinished job
	 * @return

	 * @require
	  	- REQUIRE(properlyInitialized(), "Class is not properly initialized");
	 */
	Job *getFirstUnfinishedJob() const;

	/**
	 * \brief Gets the first unprocessed job
	 * @return

	 * @require
	  	- REQUIRE(properlyInitialized(), "Class is not properly initialized");
	  	- REQUIRE(!jobs.empty(), "No jobs were found");
	 */
	Job *getFirstUnprocessedJob() const;

	/**
	 * \brief Gets the devices
	 * @return A vector containing the devices
	 */
    const std::vector<Device *> &getDevices() const;

	/**
	 * \brief Gets the jobs
	 * @return A vector containing the jobs
	 */
    const std::vector<Job *> &getJobs() const;

	/**
	 * \brief Gets the unfinished jobs
	 * @return A vector containing the unfinished jobs
	 */
	std::vector<Job *> getUnfinishedJobs() const;

	/**
	 * \brief Gets the log errors
	 * @return A boolean indicating if the errors are logged
	 */
    bool isLogErrors() const;

	/**
	 * \brief Set if the errors should be logged
	 * @param logErrors
	 */
    void setLogErrors(bool logErrors);

	/**
	 * \brief Set if the messages should be logged
	 * @param log
	 */
	void setLogMessages(bool log);

	/**
	 * \brief Prints the report
	 * \return A string containing the report

	 * @require
		- REQUIRE(properlyInitialized(), "Class is not properly initialized");
		- REQUIRE(VerifyConsistency(), "Printing system is inconsistent");
	 */
    std::string printReport() const;

	/**
	 * \brief Verifies the consistency of the system, prints errors if inconsistent and logs are enabled
	 * @return A boolean indicating if the system is consistent

	 * @require
	 	- REQUIRE(properlyInitialized(), "Class is not properly initialized");
	 */
    bool VerifyConsistency() const;

	/**
	 * \brief Gets the device with the least load
	 * @return A pointer to the device with the least load

	 * @require
	 	- REQUIRE(properlyInitialized(), "Class is not properly initialized");
	 	- REQUIRE(!devices.empty(), "No devices were found.");
	 */
	Device *getDeviceWithLeastLoad() const;

	/**
	 * \brief Gets the device with the least load
	 * @return A pointer to the device with the least load

	 * @require
	 	- REQUIRE(properlyInitialized(), "Class is not properly initialized");
	 	- REQUIRE(!devices.empty(), "No devices were found.");
	 	- REQUIRE(job->getAssignedTo() == NULL, "Job is already assigned to a device.");
	 */
	Device *assignJobToDevice(Job *job) const;

	/**
	 * \brief Assigns all jobs to devices

	 * @require
		- REQUIRE(properlyInitialized(), "System is not properly initialized.");
		- REQUIRE(!jobs.empty(), "No jobs were found");
		- REQUIRE(!devices.empty(), "No devices were found");
	 */
	void assignAllJobs() const;

	/**
	 * \brief Processes the first job

	 * @require
		- REQUIRE(properlyInitialized(), "System is not properly initialized.");
		- REQUIRE(!jobs.empty(), "No jobs were found");
		- REQUIRE(!devices.empty(), "No devices were found");
		- REQUIRE(getFirstUnprocessedJob() != NULL, "All jobs are processed");
		- REQUIRE(getFirstUnprocessedJob()->getAssignedTo() != NULL, "Job is not assigned to a device");

	 * @ensure
		- ENSURE(job->isFinished(), "Job is not finished");
		- ENSURE(job->getAssignedTo()->getLoad() != initialLoad, "Device did not process the job");
	 */
	void processFirstJob() const;

	/**
	 * \brief Processes all jobs

	 * @require
		- REQUIRE(properlyInitialized(), "System is not properly initialized");

	 * @ensure
		- ENSURE(log_file_name == log_file, "Log file is not set");
	 */
	void setLogFile(const std::string &log_file_name);

	/**
	 * \brief Processes all jobs
	 * @return A string containing the result of the processing


	 * @require
    	- REQUIRE(properlyInitialized(), "System is not properly initialized");

     * @ensure
    	- ENSURE(getFirstUnprocessedJob() == NULL, "Not all pages were printed");
	 */
    void processAll();

private:
	/**
	 * \brief Checks if a num is not negative
	 * @param s
	 * @return A boolean indicating if num is not negative
	 */
	static bool CheckNotNegative(int num);

private:
    System* _init;
    std::vector<Device *> devices;
    std::vector<Job *> jobs;
    bool log_errors;
	std::string log_file_name;
	bool log = false;
};


#endif //PRINTSYSTEM_SYSTEM_H
