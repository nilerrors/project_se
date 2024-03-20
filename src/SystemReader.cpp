//
// Created by nilerrors on 3/20/24.
//

#include "SystemReader.h"
#include "DesignByContract.h"
#include "utils.h"

void SystemReader::ReadData(const std::string &file_name) {
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

	doc.Clear();
}

void SystemReader::ReadDevice(TiXmlElement *device_element) {
	REQUIRE(device_element!= NULL, "device_element is a NULL pointer");
	try {
		Device* device = new Device(device_element);
		devices->push_back(device);

		ENSURE(!devices->empty(), "No devices were read after reading xml file");
	}
	catch (const std::runtime_error& error) {
		logger->error(error.what());
	}
}

void SystemReader::ReadJob(TiXmlElement *job_element) {
	REQUIRE(job_element!= NULL, "job_element is a NULL pointer");
	try {
		Job* job = new Job(job_element);
		jobs->push_back(job);

		ENSURE(!jobs->empty(), "No Jobs were read after reading xml file");
	}
	catch (const std::runtime_error& error) {
		logger->error(error.what());
	}
}
