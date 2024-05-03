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
     * @require
         - REQUIRE(device->properlyInitialized(), "Device is not properly initialized");
         - REQUIRE(device!= NULL, "Device is NULL");
         - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");

      * @ensure
         - ENSURE(std::find(devices.begin(), devices.end(), device) != devices.end(), "Device was not added to devices");
     */
    void addDevice(Device *device);

    /**
     * \brief Adds a job to the system
     * @param job
     * @require
         - REQUIRE(job->properlyInitialized(), "Job is not properly initialized");
         - REQUIRE(job!= NULL, "Job is NULL");
         - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");

      * @ensure
         - ENSURE(std::find(jobs.begin(), jobs.end(), job) != jobs.end(), "Job was not added to jobs");
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
          - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
     */
    Device *getFirstDevice() const;

    /**
     * \brief Gets the first job
     * @return

     * @require
          - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
     */
    Job *getFirstJob() const;

    /**
     * \brief Gets the first unfinished job
     * @return

     * @require
          - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
     */
    Job *getFirstUnfinishedJob() const;

    /**
     * \brief Gets the first unprocessed job
     * @return

     * @require
          - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
          - REQUIRE(!jobs.empty(), "No jobs were found");
     */
    Job *getFirstUnprocessedJob() const;

    /**
     * \brief Gets the devices
     * @return A vector containing the devices
     *
     * @require
         - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
     */
    const std::vector<Device *> &getDevices() const;

    /**
     * \brief Gets the jobs
     * @return A vector containing the jobs
     *
     * @require
         - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
     */
    const std::vector<Job *> &getJobs() const;

    /**
     * \brief Gets the unfinished jobs
     * @return A vector containing the unfinished jobs
     *
     * @require
         - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
     */
    std::vector<Job *> getUnfinishedJobs() const;

    /**
     * \brief Gets the device with the least load
     * @param deviceType
     * @return A pointer to the device with the least load

     * @require
         - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
         - REQUIRE(!devices.empty(), "No devices were found.");
     */
    Device *getDeviceWithLeastLoadOfType(std::string deviceType) const;

    /**
     * \brief Moves the job to unassignable jobs
     * @param job
     * @require
         - REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
         - REQUIRE(job_at != jobs.end(), "Job was not found in the jobs");

    * @ensure
        - ENSURE(std::find(unassignable_jobs.begin(), unassignable_jobs.end(), job) != unassignable_jobs.end(), "Job was not moved to unassignable jobs");
     */
    void setJobUnassignable(Job *job);

private:
    SystemManager *_init;

    std::vector<Device *> devices;
    //Add three more vectors bw_devices, color_devices, scan_devices? Also change devices to all_devices?
    std::vector<Job *> jobs;

    // Jobs for which there are no compatible devices (devices of the same type).
    std::vector<Job *> unassignable_jobs;
};


#endif //PRINTSYSTEM_SYSTEMMANAGER_H
