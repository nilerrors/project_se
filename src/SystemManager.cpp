//
// Created by nilerrors on 3/28/24.
//

#include <algorithm>
#include "SystemManager.h"
#include "lib/DesignByContract.h"

SystemManager::SystemManager() {
    _init = this;
}

SystemManager::~SystemManager()
{
    for(Device*& device : devices){
        delete device;
    }
    for(Job*& job : jobs){
        delete job;
    }
    devices.clear();
    jobs.clear();
}


Device *SystemManager::getFirstDevice() const {
    REQUIRE(properlyInitialized(), "Class is not properly initialized");
    return devices.empty() ? nullptr : devices.front();
}

Job *SystemManager::getFirstJob() const {
    REQUIRE(properlyInitialized(), "Class is not properly initialized");
    return jobs.empty() ? nullptr : jobs.front();
}

Job *SystemManager::getFirstUnfinishedJob() const {
    for(Job *job : jobs){
        if(job->getStatus() != Job::done) {
            return job;
        }
    }
    return NULL;
}

Job *SystemManager::getFirstUnprocessedJob() const {
    REQUIRE(properlyInitialized(), "System is not properly initialized");
    REQUIRE(!jobs.empty(), "No jobs were found");
    for(Job *job : jobs){
        if(job->getStatus() == Job::assigned) {
            return job;
        }
    }
    return NULL;
}

const std::vector<Device *> &SystemManager::getDevices() const {
    return devices;
}

const std::vector<Job *> &SystemManager::getJobs() const {
    return jobs;
}

std::vector<Job *> SystemManager::getUnfinishedJobs() const {
    std::vector<Job *> unfinished_jobs;
    for(Job *job : jobs){
        if(job->getStatus() != Job::done) {
            unfinished_jobs.push_back(job);
        }
    }
    return unfinished_jobs;
}

Device *SystemManager::getDeviceWithLeastLoadOfType(std::string deviceType) const {
    REQUIRE(properlyInitialized(), "System is not properly initialized.");
    REQUIRE(!devices.empty(), "No devices were found.");

    Device *least_loaded_device = NULL;
    for(Device *device : devices) {
        if(device->getType() == deviceType
            && (least_loaded_device == NULL
                || device->getLoad() < least_loaded_device->getLoad())) {
            least_loaded_device = device;
        }
    }
    return least_loaded_device;
}

void SystemManager::addDevice(Device *device) {
    REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
    REQUIRE(device->properlyInitialized(), "Device is not properly initialized");
    REQUIRE(device != NULL, "Device is NULL");

    devices.push_back(device);

    ENSURE(std::find(devices.begin(), devices.end(), device) != devices.end(), "Device must be present in the devices");
}

void SystemManager::addJob(Job *job) {
    REQUIRE(properlyInitialized(), "SystemManager is not properly initialized");
    REQUIRE(job->properlyInitialized(), "Job is not properly initialized");
    REQUIRE(job!= NULL, "Job is NULL");

    jobs.push_back(job);

    ENSURE(std::find(jobs.begin(), jobs.end(), job) != jobs.end(), "Job must be present in the jobs");
}

void SystemManager::setJobUnassignable(Job *job) {
    std::vector<Job *>::const_iterator job_at = std::find(jobs.begin(), jobs.end(), job);
    REQUIRE(job_at != jobs.end(), "Job was not found in the jobs");

    jobs.erase(job_at);

    unassignable_jobs.push_back(job);

    ENSURE(std::find(unassignable_jobs.begin(), unassignable_jobs.end(), job) != unassignable_jobs.end(),
           "Job must be present in the unassignable jobs");
}
