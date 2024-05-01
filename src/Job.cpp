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
    type = StringToPrintingType(temp_type);
}

int Job::getJobNumber() const {
    return jobNumber;
}

int Job::getPageCount() const {
    return pageCount;
}

int Job::getPrintedPageCount() const {
    return printedPageCount;
}

void Job::increasePrintedPageCount() {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    REQUIRE(printedPageCount < pageCount, "Printed page count should be less than total page count");
    printedPageCount++;

    ENSURE(printedPageCount <= pageCount, "Printed page count should be less than total page count");
}

const std::string &Job::getUserName() const {
    return userName;
}

Job::Status Job::getStatus() const
{
    return status;
}

void Job::setStatus(Job::Status stat) {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    status = stat;

    ENSURE(status == stat, "Status is not set correctly");
}

Device *Job::getAssignedTo() const
{
	return assignedTo;
}

void Job::setAssignedTo(Device *assigned)
{
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    REQUIRE(assigned != NULL, "Job is not assigned to a device");
	assignedTo = assigned;

    ENSURE(assignedTo == assigned, "Device is not assigned correctly");
}

int Job::getQueueNumber() const {
    if (status != assigned) return -1;
    int current_waiting = -1;
    for(size_t i = 0; i < assignedTo->getJobs().size(); i++) {
        Job *current_job = assignedTo->getJobs()[i];
        if (current_job->status == waiting || current_job->status == assigned)
        {
            current_waiting++;
        }
        if(current_job->getJobNumber() == jobNumber) {
            return current_waiting;
        }
    }

    return current_waiting;
}

PrintingType Job::getType() const {
    return type;
}
