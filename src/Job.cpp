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

Job::Status Job::getStatus() const
{
    return status;
}

void setStatus()
{

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

Job::JobTypes Job::stringtoType(std::string &typstr) {
    if(typstr == "bw") {
        return Job::JobTypes::bw;
    }
    else if(typstr == "scan"){
        return Job::JobTypes::scan;
    }
    else {
        return Job::JobTypes::color;
    }
}

std::string Job::printReport() const
{

    REQUIRE(properlyInitialized(), "Class is not properly initialized.");
    REQUIRE(jobNumber >= 0, "JobNumber is negative.");
    REQUIRE(pageCount >= 0, "PageCount is negative.");
    REQUIRE(printedPageCount>=0, "PrintedPageCount is negative");
    REQUIRE(isValidJobType(job_type_to_string(type)), "Type is not defined");

    std::stringstream report;

    report << "[Job #" << jobNumber << "]" << std::endl;
    report << "* Owner: " << userName << std::endl;
    report << "* Device: " << assignedTo->getName() << std::endl;
    report << "* Status: " << printedPageCount << " pages done" << std::endl;
    report << "* Total pages: " << pageCount << " pages" << std::endl;
    report << "* Total CO2: " << assignedTo->getEmission() * printedPageCount << "g CO2" << std::endl;
    report << "* Total cost: " << assignedTo->getCost() * printedPageCount << " cents" << std::endl;


    ENSURE(!report.str().empty(), "Job report is empty");
    return report.str();


}

std::string Job::job_type_to_string(Job::JobTypes device_type) {
    switch (device_type) {
        case JobTypes::bw:
            return "Black-and-white";
        case JobTypes::color:
            return "Color";
        case JobTypes::scan:
            return "Scan";
    }
}
