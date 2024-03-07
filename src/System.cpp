//
// Created by student on 29/02/24.
//

#include "DesignByContract.h"
#include "utils.h"
#include "System.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
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
        else{
            std::cerr << "Unrecognizable element"<<std::endl;
            continue;
        }
    }
}

void System::ReadDevice(TiXmlElement *device_element) {
    REQUIRE(device_element!= NULL, "device_element is a NULL pointer");
    try {
        Device* device = new Device(device_element);
        devices.push_back(device);

        ENSURE(!devices.empty(), "No devices were read after reading xml file");
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
    }
}

void System::ReadJob(TiXmlElement *job_element) {
    REQUIRE(job_element!= NULL, "job_element is a NULL pointer");
    try {
        Job* job = new Job(job_element);
        jobs.push_back(job);

        ENSURE(!jobs.empty(), "No Jobs were read after reading xml file");
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
    for (Device *&device: devices) {
        delete device;
        device = NULL;
    }
    for (Job *&job: jobs) {
        delete job;
        job = NULL;
    }
}

std::string System::printReport() const {
    /*
     Generate a .txt file detailing the contents of the system. The file will contain information about all printers and jobs of the system respectively.
     return: Filename van de report
     */
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d-%X");
    std::string filename = "reports/report-" + ss.str() + REPORT_FILE_EXTENSION;
    std::ofstream report(filename);
    report << "PRINTERS:" << std::endl;
    for(Device *i : devices) {
        report << "\t *" +  i->getName() << std::endl;
    }
    report << "JOBS:" << std::endl;
    for(Job* i : jobs) {
        report << "\t *[" +  std::to_string(i->getJobNumber())+ "|"  << i->getUserName() +"]" << std::endl;
    }
    report.close();
    return filename;
}

bool System::VerifyConsistency() const {
    REQUIRE(properlyInitialized(),  "Class is not properly initialized.");

    std::vector<int> job_nums{};
    ///Check if PageCount and JobNumber are not negative
    for(Job *const& job : jobs){
        if(!CheckNotNegative(job->getPageCount())){
            std::cerr << "[Inconsistent printing system" <<std::endl;
            return false;
        }
        else if(!CheckNotNegative(job->getJobNumber())){
            std::cerr << "[Inconsistent printing system" <<std::endl;
            return false;
        }

        if(std::find(job_nums.begin(), job_nums.end(),job->getJobNumber()) != job_nums.end()){
            std::cerr << "[Inconsistent printing system" <<std::endl;
            return false;
        }
        else{
            job_nums.push_back(job->getJobNumber());
        }
    }

    ///Check if Emission and Speed are not negative
    for(Device *const &device : devices){
        if(!CheckNotNegative(device->getEmission())){
            std::cerr << "[Inconsistent printing system" <<std::endl;
            return false;
        }
        else if(!CheckNotNegative(device->getSpeed())){
            std::cerr << "[Inconsistent printing system" <<std::endl;
            return false;
        }
    }


    return true;
}

bool System::CheckNotNegative(int num) {
    return num*-1 < 0;
}
