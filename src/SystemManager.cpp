//
// Created by nilerrors on 3/28/24.
//

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

Device *SystemManager::getDeviceWithLeastLoadOfType(PrintingType deviceType) const {
    REQUIRE(properlyInitialized(), "System is not properly initialized.");
    REQUIRE(!devices.empty(), "No devices were found.");

    Device *least_loaded_device = devices.front();
    for(Device *device : devices){
        if(device->getLoad() < least_loaded_device->getLoad() && device->getType() == deviceType){
            least_loaded_device = device;
        }
    }
    return least_loaded_device;
}

void SystemManager::addDevice(Device *device) {
    devices.push_back(device);
}

void SystemManager::addJob(Job *job) {
    jobs.push_back(job);
}
