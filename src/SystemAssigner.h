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

    void setLogger(Logger *logger);

private:
    SystemAssigner *_init;
    SystemManager *manager;
    Logger *logger = nullptr;
};


#endif //PRINTSYSTEM_SYSTEMASSIGNER_H
