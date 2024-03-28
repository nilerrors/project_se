//
// Created by student on 29/02/24.
//

#include <iostream>
#include <sstream>
#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "Job.h"
#include "Device.h"

Job::Job(int jobNumber, int pageCount, const std::string &userName) : jobNumber(jobNumber), pageCount(pageCount),
                                                                      userName(userName) {}

Job::Job(TiXmlElement *job_element) {
	std::string temp_jobNumber;
	std::string temp_pageCount;
	std::string temp_userName;
    std::string temp_type;

	for (TiXmlNode *node = job_element->FirstChild(); node != NULL; node = node->NextSibling()) {
		if (node->FirstChild() == NULL) {
			continue;
		}
		if (std::string(node->Value()) == "jobNumber") {
			temp_jobNumber = node->FirstChild()->Value();
		} else if (std::string(node->Value()) == "pageCount") {
			temp_pageCount = node->FirstChild()->Value();
		} else if (std::string(node->Value()) == "userName") {
			temp_userName = node->FirstChild()->Value();
		} else if(std::string(node->Value()) == "type") {
            temp_type = node->FirstChild()->Value();
        } else {
            EXPECT(false, "Unknown attribute for Device: '" + std::string(node->Value()) + "'");
		}
	}

	EXPECT(!temp_jobNumber.empty(), "No job number is provided");
	EXPECT(!temp_pageCount.empty(), "No page count is provided");
	EXPECT(is_number(temp_jobNumber) , "Job number should be a number");
	EXPECT(is_number(temp_pageCount) , "Page count should be a number");
	EXPECT(!temp_userName.empty(), "No user name is provided");
    EXPECT(!temp_type.empty(), "No type is provided");
    EXPECT(isValidDeviceType(temp_type), "Type should be a valid job type");

	jobNumber = std::stoi(temp_jobNumber);
	pageCount = std::stoi(temp_pageCount);
	userName = temp_userName;
	init_ = this;
    type = stringtoType(temp_type);
}

int Job::getJobNumber() const {
    return jobNumber;
}

int Job::getPageCount() const {
    return pageCount;
}

const std::string &Job::getUserName() const {
    return userName;
}

bool Job::isFinished() const
{
	return finished;
}

void Job::setFinished(bool finish)
{
	finished = finish;
}

bool Job::isInProcess() const
{
	return inProcess;
}

void Job::setInProcess(bool process)
{
	inProcess = process;
}

Device *Job::getAssignedTo() const
{
	return assignedTo;
}

void Job::setAssignedTo(Device *assigned)
{
	assignedTo = assigned;
}

std::string Job::finishMessage() const
{
	REQUIRE(properlyInitialized(), "Job is not properly initialized");
	REQUIRE(assignedTo != NULL, "Job is not assigned to a device");

	std::stringstream message;

	message << "Printer " << '"' << assignedTo->getName() << '"' << " finished job:" << std::endl;
	message << "\tNumber: " << jobNumber << std::endl;
	message << "\tSubmitted by " << '"' << userName << '"' << std::endl;
	message << "\t" << pageCount << " pages" << std::endl;

	return message.str();
}

Job::types Job::stringtoType(std::string &typstr) {
    if(typstr == "bw") {
        return Job::types::bw;
    }
    else if(typstr == "scan"){
        return Job::types::scan;
    }
    else {
        return Job::types::color;
    }
}
