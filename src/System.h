//
// Created by student on 29/02/24.
//

#ifndef PRINTSYSTEM_SYSTEM_H
#define PRINTSYSTEM_SYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include "lib/tinyxml.h"
#include "Device.h"
#include "Job.h"
#include "Logger.h"
#include "Reporter.h"
#include "SystemReader.h"
#include "SystemAssigner.h"
#include "SystemManager.h"
#include "SystemTracker.h"

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
     * \brief Checks if the class is properly
     * @return A boolean indicating if the class is properly initialized
     */
    bool properlyInitialized() const { return _init == this; }

    /**
     * \brief Get System Manager
     * @return A pointer to the System Manager
     */
    SystemManager *getManager() const;

    /**
     * \brief Get Logger
     * @return A pointer to the Logger
     * @require
     * - REQUIRE(properlyInitialized(), "System is not properly initialized.");
     */
    Logger *getLogger() const;

    /**
     * \brief Get System Reader
     * @return A pointer to the System Reader
     * @require
     * - REQUIRE(properlyInitialized(), "System is not properly initialized.");
     */
    SystemReader *getReader() const;

    /**
     * \brief Get System Assigner
     * @return A pointer to the System Assigner
     * @require
     * - REQUIRE(properlyInitialized(), "System is not properly initialized.");
     */
    SystemAssigner *getAssigner() const;


    /**
     * \brief Get System Tracker
     * @return A pointer to the System Tracker
     * @require
     * - REQUIRE(properlyInitialized(), "System is not properly initialized.");
     */
    SystemTracker*getTracker() const;

	/**
	 * \brief Clears the system
	 * @require
	 *   - REQUIRE(properlyInitialized(), "System is not properly initialized.");
	 */
    void clear();

	/**
	 * \brief Reads the data from the file
	 * @param file_name

	 * @require
		- REQUIRE(properlyInitialized(), "System is not properly initialized.");
		- REQUIRE(FileExists(file_name), "File does not exist.");
	 */
    void ReadData(const std::string &file_name);

	/**
	 * \brief Prints the report
	 * \param reporter

	 * @require
		- REQUIRE(properlyInitialized(), "System is not properly initialized");
		- REQUIRE(VerifyConsistency(), "Printing system is inconsistent");
	 */
    void printReport(Reporter *reporter) const;

	/**
	 * \brief Verifies the consistency of the system, prints errors if inconsistent and logs are enabled
	 * @return A boolean indicating if the system is consistent

	 * @require
	 	- REQUIRE(properlyInitialized(), "System is not properly initialized");

	 */
    bool VerifyConsistency() const;

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
	 * @return A string containing the result of the processing


	 * @require
    	- REQUIRE(properlyInitialized(), "System is not properly initialized");

     * @ensure
    	- ENSURE(getFirstUnprocessedJob() == NULL, "Not all pages were printed");
	 */
    void processAll();

	/**
	 * \brief Sets the logger to the given logger
	 * @param logger

	 * @require
	 	- REQUIRE(properlyInitialized(), "System is not properly initialized");
	 	- REQUIRE(logger != NULL, "Logger is a NULL pointer");

	 * @ensure
	 	- ENSURE(logger == logger, "Logger was not set");
	 */
	 void setLogger(Logger *logger);

     /**
      * \brief Prints the current state of the system in an advanced way
      * @return string
      * @require
      * - REQUIRE(properlyInitialized(), "System is not properly initialized");
      * - REQUIRE(VerifyConsistency(), "Printing system is inconsistent");
      */
     void AdvancePrintReport(Reporter *reporter);

private:
    System* _init;
    bool wait_for_print = false;

    SystemManager *manager;
    SystemTracker *tracker;
	Logger *logger;
    SystemReader *reader;
    SystemAssigner *assigner;
};


#endif //PRINTSYSTEM_SYSTEM_H
