//
// Created by nilerrors on 3/20/24.
//

#ifndef PRINTSYSTEM_SYSTEMREADER_H
#define PRINTSYSTEM_SYSTEMREADER_H


#include <vector>
#include "Job.h"
#include "Device.h"
#include "Logger.h"
#include "SystemManager.h"

class SystemReader
{
public:
    /**
     * \brief Constructor of SystemReader
     * @param manager
     * @param logger

     * @require
         - REQUIRE(manager != NULL, "manager is a null pointer");
         - REQUIRE(logger != NULL, "Logger is a NULL pointer");

     * @ensure
         - ENSURE(properlyInitialized(), "SystemReader is not properly initialized");
     */
	SystemReader(SystemManager *manager,
				 Logger *logger)
				: _init(this), manager(manager), logger(logger) {
        REQUIRE(manager != NULL, "Manager is a NULL pointer");
        REQUIRE(logger != NULL, "Logger is a NULL pointer");
        ENSURE(properlyInitialized(), "SystemReader is not properly initialized");
    }

    /**
     * \brief Destructor of SystemReader
     */
	~SystemReader() = default;

	/**
	 * \brief Checks if the class is properly initialized
	 * \return True if the class is properly initialized, false otherwise
	 */
	bool properlyInitialized() const { return _init == this; }

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
     * \brief Sets the logger of SystemReader
     * @param logger
     * @require
         - REQUIRE(properlyInitialized(), "SystemReader is not properly initialized");
         - REQUIRE(logger != NULL, "Logger is a NULL pointer");

     * @ensure
         - ENSURE(logger == log, "Logger was not set");
     */
    void setLogger(Logger *logger);

private:
	SystemReader *_init = nullptr;
	SystemManager *manager;
	Logger *logger;
};


#endif //PRINTSYSTEM_SYSTEMREADER_H
