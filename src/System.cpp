//
// Created by student on 29/02/24.
//

#include "DesignByContract.h"
#include "utils.h"
#include "System.h"

System::System() {
    _init = this;
}

System::~System() {
    _init = NULL;
    this->clear();
}

void System::ReadData(const std::string &file_name) {
    REQUIRE(properlyInitialized(), "Class is not properly initialized.");
    REQUIRE(FileExists(file_name), "File does not exist.");

    TiXmlDocument doc;
    if (!doc.LoadFile(file_name.c_str())) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to read the file: No SYSTEM root." << std::endl;
        return;
    }
    if (std::string(root->Value()) != "SYSTEM")
    {
        std::cerr << "Failed to read the file: Unexpected root '"
                    << root->Value() << "', Expected 'SYSTEM'." << std::endl;
    }

    for (TiXmlElement *elm = root->FirstChildElement(); elm != NULL; elm = elm->NextSiblingElement())
    {
        if (std::string(elm->Value()) == "DEVICE") {
            ReadDevice(elm);
        } else if (std::string(elm->Value()) == "JOB") {
            ReadJob(elm);
        }
    }
}

void System::ReadDevice(TiXmlElement *device_element) {
    try {
        Device* device = new Device(device_element);
        devices.push_back(device);
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
    }
}

void System::ReadJob(TiXmlElement *job_element) {
    try {
        Job* job = new Job(job_element);
        jobs.push_back(job);
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
    }
}

Device *System::getFirstDevice() const {
    return devices.empty() ? nullptr : devices.front();
}

Job *System::getFirstJob() const {
    return jobs.empty() ? nullptr : jobs.front();
}

const std::vector<Device *> &System::getDevices() const {
    return devices;
}

const std::vector<Job *> &System::getJobs() const {
    return jobs;
}

void System::clear() {
    for (auto &device : devices) {
        delete device;
        device = NULL;
    }
    for (auto &job : jobs) {
        delete job;
        job = NULL;
    }
}
