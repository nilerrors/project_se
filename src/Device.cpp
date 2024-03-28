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
        } else {
            EXPECT(false, "Unknown attribute for Device: '" + std::string(node->Value()) + "'");
        }
    }

    EXPECT(!temp_name.empty(), "No name is provided");
    EXPECT(!temp_emission.empty(), "No emission is provided");
    EXPECT(is_number(temp_emission) , "Emission should be an integer number");
    EXPECT(!temp_speed.empty(), "No speed is provided");
    EXPECT(is_number(temp_speed) , "Speed should be an integer number");

    name = temp_name;
    emission = std::stoi(temp_emission);
    speed = std::stoi(temp_speed);
    init_ = this;
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

	std::stringstream report;
	report << name << " (CO2: " << emission << "g/page)" << ":" << std::endl;
	if (jobs.empty()) {
		report << "\t" << "No jobs" << std::endl;

        return report.str();
	}
	report << "\t* Current:" << std::endl;
	report << "\t\t[#" +  std::to_string(jobs.front()->getJobNumber())+ "|"  << jobs.front()->getUserName() +"]" << std::endl;
	if (jobs.size() > 1)
	{
		report << "\t* Queue:" << std::endl;
		for(size_t i = 1; i < jobs.size(); i++) {
			Job *job = jobs[i];
			report << "\t\t[#" +  std::to_string(job->getJobNumber())+ "|"  << job->getUserName() +"]" << std::endl;
		}
	}

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

	std::chrono::milliseconds duration(job->getPageCount() / speed * 60 * 1000);
	std::this_thread::sleep_for(duration);

	job->setInProcess(false);
	job->setFinished(true);
	jobs.pop_front();

	ENSURE(jobs.front() != job, "Job is not removed");
	ENSURE(job->isFinished(), "Job is not finished.");

	return job->finishMessage();
}
