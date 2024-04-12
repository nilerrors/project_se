//
// Created by nilerrors on 3/28/24.
//

#include "SystemAssigner.h"
#include "lib/DesignByContract.h"

SystemAssigner::SystemAssigner(SystemManager *manager,
                               Logger *logger) : manager(manager), logger(logger) {
    _init = this;
}


SystemAssigner::~SystemAssigner() = default;

Device *SystemAssigner::assignJobToDevice(Job *job) const {
    REQUIRE(properlyInitialized(), "SystemAssigner is not properly initialized");
    REQUIRE(!manager->getDevices().empty(), "No devices were found");
    REQUIRE(job->getAssignedTo() == NULL, "Job is already assigned to a device.");

    //Add exception here:  [No device exists for the specified job type] Print an error message that the job could not be
    //printed.
    Device *device = manager->getDeviceWithLeastLoad();
    device->addJob(job);
    job->setAssignedTo(device);
    return device;
}

void SystemAssigner::assignAllJobs() const {
    REQUIRE(properlyInitialized(), "SystemAssigner is not properly initialized");
    REQUIRE(!manager->getJobs().empty(), "No jobs were found");
    REQUIRE(!manager->getDevices().empty(), "No devices were found");

    for (Job *job : manager->getJobs())
    {
        if (job->getAssignedTo() == NULL)
        {
            assignJobToDevice(job);
            job->setStatus(Job::assigned);
        }
    }
}

void SystemAssigner::setLogger(Logger *log) {
    REQUIRE(properlyInitialized(), "System is not properly initialized");
    REQUIRE(log != NULL, "Logger is a NULL pointer");
    logger = log;
    ENSURE(logger == log, "Logger was not set");
}
