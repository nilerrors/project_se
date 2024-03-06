//
// Created by student on 29/02/24.
//

#include <iostream>
#include "DesignByContract.h"
#include "utils.h"
#include "Job.h"

Job::Job(int jobNumber, int pageCount, const std::string &userName) : jobNumber(jobNumber), pageCount(pageCount),
                                                                      userName(userName) {}

Job::Job(TiXmlElement *job_element) {
	std::string temp_jobNumber;
	std::string temp_pageCount;
	std::string temp_userName;

	for (TiXmlNode *node = job_element->FirstChild(); node != NULL; node = node->NextSibling()) {
		if (node->FirstChild() == NULL) {
			std::cerr << "'" << node->Value() << "' is not allowed to be empty" << std::endl;
			continue;
		}
		if (std::string(node->Value()) == "jobNumber") {
			temp_jobNumber = node->FirstChild()->Value();
		} else if (std::string(node->Value()) == "pageCount") {
			temp_pageCount = node->FirstChild()->Value();
		} else if (std::string(node->Value()) == "userName") {
			temp_userName = node->FirstChild()->Value();
		} else {
			std::cerr << "Unknown attribute for Device: '" << node->Value() << "'" << std::endl;
		}
	}

	ENSURE(!temp_jobNumber.empty(), "No job number is provided");
	ENSURE(!temp_pageCount.empty(), "No page count is provided");
	ENSURE(is_number(temp_jobNumber) , "Job number should be a number");
	ENSURE(is_number(temp_pageCount) , "Page count should be a number");
	ENSURE(!temp_userName.empty(), "No user name is provided");

	jobNumber = std::stoi(temp_jobNumber);
	pageCount = std::stoi(temp_pageCount);
	userName = temp_userName;
	init_ = this;
}
