//
// Created by student on 2/05/24.
//

#include "JobScan.h"

JobScan::JobScan(TiXmlElement *job_element) : Job(job_element) {}

JobScan::JobScan(int jobNumber, int pageCount, const std::string &userName) : Job(jobNumber, pageCount, userName) {}

JobScan::~JobScan() {}

std::string JobScan::getType() {
    return "scanning job";
}
