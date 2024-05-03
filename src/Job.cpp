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
                                                                      userName(userName) {
    ENSURE(getJobNumber() == jobNumber, "Job number is not set correctly");
    ENSURE(getPageCount() == pageCount, "Page count is not set correctly");
    ENSURE(getUserName() == userName, "User name is not set correctly");
    ENSURE(getStatus() == Status::unassigned, "Status is not set correctly");
    ENSURE(getPrintedPageCount() == 0, "Printed page count is not set correctly");
    ENSURE(properlyInitialized(), "Job is not properly initialized");
}
int Job::getJobNumber() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return jobNumber;
}

int Job::getPageCount() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return pageCount;
}

int Job::getPrintedPageCount() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return printedPageCount;
}

void Job::increasePrintedPageCount() {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    REQUIRE(printedPageCount < pageCount, "Printed page count should be less than total page count");
    printedPageCount++;

    ENSURE(printedPageCount <= pageCount, "Printed page count should be less than total page count");
}

const std::string &Job::getUserName() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return userName;
}

Job::Status Job::getStatus() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return status;
}

void Job::setStatus(Job::Status stat) {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    status = stat;

    ENSURE(status == stat, "Status is not set correctly");
}

Device *Job::getAssignedTo() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return assignedTo;
}

void Job::setAssignedTo(Device *assigned) {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    REQUIRE(assigned != NULL, "Job is not assigned to a device");
    assignedTo = assigned;

    ENSURE(assignedTo == assigned, "Device is not assigned correctly");
}

int Job::getQueueNumber() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    REQUIRE(getAssignedTo() != NULL, "Job is not assigned to a device");

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
