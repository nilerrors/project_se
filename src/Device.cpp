//
// Created by student on 29/02/24.
//

#include "lib/DesignByContract.h"
#include "Device.h"
#include "lib/utils.h"
#include "System.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>

Device::Device(const std::string &name, int emission, int speed) : name(name), emission(emission), speed(speed) {}

Device::Device(TiXmlElement *device_node) {
    std::string temp_name;
    std::string temp_emission;
    std::string temp_speed;
    std::string temp_type;
    std::string temp_cost;

    for (TiXmlNode *node = device_node->FirstChild(); node != nullptr; node = node->NextSibling()) {
        if (node->FirstChild() == nullptr) {
            continue;
        }
        if (std::string(node->Value()) == "name") {
            temp_name = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "emission") {
            temp_emission = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "speed") {
            temp_speed = node->FirstChild()->Value();
        } else if(std::string(node->Value()) == "type") {
            temp_type = node->FirstChild()->Value();
        } else if(std::string(node->Value()) == "cost") {
            temp_cost = node->FirstChild()->Value();
        }
        else {
            EXPECT(false, "Unknown attribute for Device: '" + std::string(node->Value()) + "'");
        }
    }

    EXPECT(!temp_name.empty(), "No name is provided");
    EXPECT(!temp_emission.empty(), "No emission is provided");
    EXPECT(is_number(temp_emission) , "Emission should be an integer number");
    EXPECT(!temp_speed.empty(), "No speed is provided");
    EXPECT(is_number(temp_speed) , "Speed should be an integer number");
    EXPECT(!temp_type.empty(), "No type is provided");
    EXPECT(isValidDeviceType(temp_type), "Type should be a valid device type");
    EXPECT(!temp_cost.empty(), "No cost is provided");
    EXPECT(is_number(temp_cost), "Cost should be an integer number");

    name = temp_name;
    emission = std::stoi(temp_emission);
    speed = std::stoi(temp_speed);
    init_ = this;
    type = stringtoType(temp_type);
    cost = std::stoi(temp_cost);
}

const std::string &Device::getName() const {
    return name;
}

int Device::getEmission() const {
    return emission;
}

int Device::getSpeed() const {
    return speed;
}

void Device::addJob(Job *job)
{
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	REQUIRE(job != NULL, "Job is empty.");
    job->setAssignedTo(this);
	jobs.push_back(job);
	ENSURE(jobs.back() == job, "Job is not added to the device.");
}

std::string Device::printReport() const
{
	/*
	 Generate a .txt file detailing the contents of the system. The file will contain information about all printers and jobs of the system respectively.
	 return: Filename van de report
	 */
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	REQUIRE(emission >= 0, "Emission is negative.");
	REQUIRE(speed >= 0, "Speed is negative.");
    REQUIRE(cost>=0, "Cost is negative");
    REQUIRE(isValidDeviceType_2(device_type_to_string(type)), "Type is not defined");


	std::stringstream report;
    report << name << ":" << std::endl;
    report << "* CO2: " << emission << "g/page"<<std::endl;
    report << "* " << speed << " pages / minute"<<std::endl;
    report << "* " << device_type_to_string(type) << std::endl;
    report << "* " << cost << " cents / page";
    report << std::endl;


	ENSURE(!report.str().empty(), "Device report is empty");
	return report.str();
}

int Device::getLoad() const
{
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	int load = 0;
	for (Job *job : jobs)
	{
		load += job->getPageCount();
	}
	ENSURE(load >= 0, "Load is negative.");
	return load;
}

std::string Device::processJob()
{
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	REQUIRE(!jobs.empty(), "No jobs to process.");
	REQUIRE(jobs.front() != NULL, "First job is empty");

	Job *job = jobs.front();

    assert(job->getStatus() != Job::done);  // cannot process finished job

    job->increasePrintedPageCount();
    if (job->getPrintedPageCount() == job->getPageCount())
    {
        job->setStatus(Job::done);
        jobs.pop_front();
        ENSURE(jobs.front() != job, "Job is not removed");
        ENSURE(job->getStatus() == Job::done, "Job is not finished.");
    }

	return job->finishMessage();
}

Device::DeviceTypes Device::stringtoType(std::string &typstr) {
    if(typstr == "bw") {
        return Device::DeviceTypes::bw;
    }
    else if(typstr == "scan"){
        return Device::DeviceTypes::scan;
    }
    else {
        return Device::DeviceTypes::color;
    }
}

std::string Device::device_type_to_string(Device::DeviceTypes device_type) {
    switch (device_type) {
        case DeviceTypes::bw:
            return "Black-and-white printer";
        case DeviceTypes::color:
            return "Color printer";
        case DeviceTypes::scan:
            return "Scanner";
    }
    return "unknown";
}

int Device::getCost() const {
    return cost;
}

std::deque<Job *> Device::getJobs() const {
    return jobs;
}

std::string Device::AdvancePrintReport() {
    REQUIRE(properlyInitialized(), "Class is not properly initialized.");

    std::stringstream report;

    report << name << std::endl;
    if(jobs.empty()){
        report << "\t" << "|"<< std::endl;
        report<<std::endl;
        return report.str();
    }
    report << "\t" << "[" <<jobs.front()->getPageCount() - jobs.front()->getPrintedPageCount() <<"/" <<jobs.front()->getPageCount() << "]\t |\t" << std::endl;
    for(uint i = 1; i < jobs.size(); i++){
        report << "[" << jobs[i]->getPageCount()<<"]" << std::endl;
    }

    report<<std::endl;
    ENSURE(!report.str().empty(), "Advance Device report is empty");
    return report.str();
}


