//
// Created by nilerrors on 3/20/24.
//

#include "SystemReader.h"
#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "DeviceFactory.h"

void SystemReader::ReadData(const std::string &file_name) {
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	REQUIRE(FileExists(file_name), "File does not exist.");

	TiXmlDocument doc;
	if (!doc.LoadFile(file_name.c_str())) {
		logger->error(doc.ErrorDesc());
		return;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
        logger->error("Failed to read the file: No SYSTEM root.");
		return;
	}
	if (std::string(root->Value()) != "SYSTEM")
	{
        logger->error(
                "Failed to read the file: Unexpected root '" + std::string(root->Value()) + "', Expected 'SYSTEM'.");
	}

	for (TiXmlElement *elm = root->FirstChildElement(); elm != NULL; elm = elm->NextSiblingElement())
	{
		if (std::string(elm->Value()) == "DEVICE") {
			ReadDevice(elm);
		} else if (std::string(elm->Value()) == "JOB") {
			ReadJob(elm);
		}
		else{
			logger->error("Unrecognizable element");
			continue;
		}
	}

	doc.Clear();
}

void SystemReader::ReadDevice(TiXmlElement *device_element) {
	REQUIRE(device_element!= NULL, "device_element is a NULL pointer");
	try {
		Device* device = DeviceFactory(device_element).getDevice();
        manager->addDevice(device);

		ENSURE(!manager->getDevices().empty(), "No devices were read after reading xml file");
	}
	catch (const std::runtime_error& error) {
		logger->error(error.what());
	}
}

void SystemReader::ReadJob(TiXmlElement *job_element) {
	REQUIRE(job_element!= NULL, "job_element is a NULL pointer");
	try {
		Job* job = new Job(job_element);
        manager->addJob(job);

		ENSURE(!manager->getJobs().empty(), "No Jobs were read after reading xml file");
	}
	catch (const std::runtime_error& error) {
		logger->error(error.what());
	}
}

void SystemReader::setLogger(Logger *log) {
    REQUIRE(properlyInitialized(), "System is not properly initialized");
    REQUIRE(logger != NULL, "Logger is a NULL pointer");
    logger = log;
    ENSURE(logger == log, "Logger was not set");
}
