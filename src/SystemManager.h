//
// Created by nilerrors on 3/28/24.
//

#ifndef PRINTSYSTEM_SYSTEMMANAGER_H
#define PRINTSYSTEM_SYSTEMMANAGER_H

#include <vector>
#include "Device.h"
#include "Job.h"


class SystemManager {
public:
    /**
     * \brief Constructor of SystemManager.
     */
    SystemManager();

    /**
     * \brief Destructor of SystemManager.
     */
    virtual ~SystemManager();

    /**
     * \brief Adds a device to the system
     * @param device
     */
    void addDevice(Device *device);

    /**
     * \brief Adds a job to the system
     * @param job
     */
    void addJob(Job *job);

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
     * \brief Gets the device with the least load
     * @return A pointer to the device with the least load

     * @require
         - REQUIRE(properlyInitialized(), "Class is not properly initialized");
         - REQUIRE(!devices.empty(), "No devices were found.");
     */
    Device *getDeviceWithLeastLoadOfType(PrintingType deviceTypes) const;

private:
    SystemManager *_init;

    std::vector<Device *> devices;
    //Add three more vectors bw_devices, color_devices, scan_devices? Also change devices to all_devices?
    std::vector<Job *> jobs;
};


#endif //PRINTSYSTEM_SYSTEMMANAGER_H
