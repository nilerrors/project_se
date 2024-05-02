//
// Created by student on 2/05/24.
//

#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "JobFactory.h"

#include "JobBlackWhite.h"
#include "JobColor.h"
#include "JobScan.h"

JobFactory::JobFactory(TiXmlElement *job_element) {
    std::string jobNumber;
    std::string pageCount;
    std::string userName;
    std::string type;

    for (TiXmlNode *node = job_element->FirstChild(); node != NULL; node = node->NextSibling()) {
        if (node->FirstChild() == NULL) {
            continue;
        }
        if (std::string(node->Value()) == "jobNumber") {
            jobNumber = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "pageCount") {
            pageCount = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "userName") {
            userName = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "type") {
            type = node->FirstChild()->Value();
        } else {
            EXPECT(false, "Unknown attribute for Device: '" + std::string(node->Value()) + "'");
        }
    }

    EXPECT(!jobNumber.empty(), "No job number is provided");
    EXPECT(!pageCount.empty(), "No page count is provided");
    EXPECT(is_number(jobNumber), "Job number should be a number");
    EXPECT(is_number(pageCount), "Page count should be a number");
    EXPECT(!userName.empty(), "No user name is provided");
    EXPECT(!type.empty(), "No type is provided");
    EXPECT(isValidDeviceType(type), "Type should be a valid job type");

    if (type == "bw") {
        job = new JobBlackWhite(std::stoi(jobNumber), std::stoi(pageCount), userName);
    } else if (type == "color") {
        job = new JobColor(std::stoi(jobNumber), std::stoi(pageCount), userName);
    } else if (type == "scan") {
        job = new JobScan(std::stoi(jobNumber), std::stoi(pageCount), userName);
    }
}

Job *JobFactory::getJob() const {
    return job;
}
