//
// Created by nilerrors on 3/28/24.
//

#ifndef PRINTSYSTEM_SYSTEMASSIGNER_H
#define PRINTSYSTEM_SYSTEMASSIGNER_H

#include <vector>

#include "Device.h"
#include "Job.h"
#include "Logger.h"
#include "SystemManager.h"


class SystemAssigner {
public:
    /**
     * \brief Constructor
     * @param devices A pointer to a vector of devices
     * @param jobs A pointer to a vector of jobs
     * @param logger A pointer to a logger
     */
    SystemAssigner(SystemManager *manager, Logger *logger);

    /**
     * \brief Checks if the class is properly initialized
     * @return True if the class is properly initialized
     */
    bool properlyInitialized() const { return _init == this; }

    /**
     * \brief Destructor
     */
    virtual ~SystemAssigner();

    /**
     * \brief Gets the device with the least load
     * @param job A pointer to the job
     * @return A pointer to the device with the least load

     * @require
         - REQUIRE(properlyInitialized(), "SystemAssigner is not properly initialized");
         - REQUIRE(!devices.empty(), "No devices were found.");
         - REQUIRE(job->getAssignedTo() == NULL, "Job is already assigned to a device.");
     */
    Device *assignJobToDevice(Job *job) const;

    /**
     * \brief Assigns all jobs to devices

     * @require
        - REQUIRE(properlyInitialized(), "SystemAssigner is not properly initialized.");
        - REQUIRE(!jobs.empty(), "No jobs were found");
        - REQUIRE(!devices.empty(), "No devices were found");

     * @ensure
        - ENSURE(std::find(device->getJobs().begin(), device->getJobs().end(), job) != device->getJobs().end(),
            "Job was not added to the device");
        - ENSURE(job->getAssignedTo() == device, "Job was not assigned to the device");
     */
    void assignAllJobs() const;

    /**
     * \brief Sets the logger of the assigner
     * @param logger
     * @require
     * - REQUIRE(properlyInitialized(), "SystemAssigner is not properly initialized");
     * - REQUIRE(logger != NULL, "Logger is a NULL pointer");
     *
     * @ensure
     * - ENSURE(logger == logger, "Logger was not set");
     */
    void setLogger(Logger *logger);

private:
    SystemAssigner *_init;
    SystemManager *manager;
    Logger *logger = nullptr;
};


#endif //PRINTSYSTEM_SYSTEMASSIGNER_H
