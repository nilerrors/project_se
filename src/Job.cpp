//
// Created by student on 29/02/24.
//

#include <iostream>
#include <sstream>
#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "Job.h"
#include "Device.h"

Job::Job(int jobNumber, int pageCount, const std::string &userName) : init_(this), jobNumber(jobNumber),
                                                                      pageCount(pageCount),
                                                                      userName(userName) {}
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

Job::Status Job::getStatus() const {
    return status;
}

void Job::setStatus(Job::Status stat) {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    status = stat;

    ENSURE(status == stat, "Status is not set correctly");
}

Device *Job::getAssignedTo() const {
    return assignedTo;
}

void Job::setAssignedTo(Device *assigned) {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    REQUIRE(assigned != NULL, "Job is not assigned to a device");
    assignedTo = assigned;

    ENSURE(assignedTo == assigned, "Device is not assigned correctly");
}

int Job::getQueueNumber() const {
    if (status != assigned) return -1;
    int current_waiting = -1;
    for (size_t i = 0; i < assignedTo->getJobs().size(); i++) {
        Job *current_job = assignedTo->getJobs()[i];
        if (current_job->status == waiting || current_job->status == assigned) {
            current_waiting++;
        }
        if (current_job->getJobNumber() == jobNumber) {
            return current_waiting;
        }
    }

    return current_waiting;
}
