//
// Created by student on 2/05/24.
//

#include "JobScan.h"

JobScan::JobScan(int jobNumber, int pageCount, const std::string &userName) : Job(jobNumber, pageCount, userName) {}

JobScan::~JobScan() {}

std::string JobScan::getType() {
    return "scanning job";
}
