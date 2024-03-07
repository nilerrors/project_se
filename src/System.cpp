//
// Created by student on 29/02/24.
//

#include "DesignByContract.h"
#include "utils.h"
#include "System.h"

System::System() {
    _init = this;
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
    Device* device = new Device(device_element);
    devices.push_back(device);
}

void System::ReadJob(TiXmlElement *job_element) {
    Job* job = new Job(job_element);
    jobs.push_back(job);
}
