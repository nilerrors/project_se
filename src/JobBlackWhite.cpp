//
// Created by student on 2/05/24.
//

#include "lib/DesignByContract.h"
#include "JobBlackWhite.h"

JobBlackWhite::JobBlackWhite(int jobNumber, int pageCount, const std::string &userName) : JobPrint(jobNumber, pageCount,
                                                                                              userName) {
    ENSURE(getJobNumber() == jobNumber, "Job number is not set correctly");
    ENSURE(getPageCount() == pageCount, "Page count is not set correctly");
    ENSURE(getUserName() == userName, "User name is not set correctly");
    ENSURE(getStatus() == Status::unassigned, "Status is not set correctly");
    ENSURE(getPrintedPageCount() == 0, "Printed page count is not set correctly");
    ENSURE(properlyInitialized(), "Job is not properly initialized");
}

JobBlackWhite::~JobBlackWhite() {}

std::string JobBlackWhite::getType() {
    REQUIRE(properlyInitialized(), "JobBlackWhite is not properly initialized");
    return "black-and-white job";
}
