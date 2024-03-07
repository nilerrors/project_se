//
// Created by student on 29/02/24.
//

#ifndef PRINTSYSTEM_SYSTEM_H
#define PRINTSYSTEM_SYSTEM_H

#include <vector>
#include <string>
#include "tinyxml.h"
#include "Device.h"
#include "Job.h"

class System
{
public:
    System();
    virtual ~System();

    void clear();

    void ReadData(const std::string &file_name);

    void ReadDevice(TiXmlElement *device_element);
    void ReadJob(TiXmlElement *job_element);

    bool properlyInitialized() const { return _init == this; }

    Device *getFirstDevice() const;
    Job *getFirstJob() const;
    const std::vector<Device *> &getDevices() const;
    const std::vector<Job *> &getJobs() const;

private:
    System* _init;
    std::vector<Device *> devices;
    std::vector<Job *> jobs;
};


#endif //PRINTSYSTEM_SYSTEM_H
