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

    void ReadData(std::string file_name);

private:
    void ReadDevice(TiXmlElement *device_element);
    void ReadJob(TiXmlElement *job_element);

private:
    System* _init;
    std::vector<Device *> devices;
    std::vector<Device *> jobs;
};


#endif //PRINTSYSTEM_SYSTEM_H
