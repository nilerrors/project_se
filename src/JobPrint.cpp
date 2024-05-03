//
// Created by student on 2/05/24.
//

#include "lib/DesignByContract.h"
#include "JobPrint.h"

JobPrint::JobPrint(int jobNumber, int pageCount, const std::string &userName) : Job(jobNumber, pageCount, userName) {
   	ENSURE(getJobNumber() == jobNumber, "Job number is not set correctly");
   	ENSURE(getPageCount() == pageCount, "Page count is not set correctly");
   	ENSURE(getUserName() == userName, "User name is not set correctly");
   	ENSURE(getStatus() == Status::unassigned, "Status is not set correctly");
   	ENSURE(getPrintedPageCount() == 0, "Printed page count is not set correctly");
   	ENSURE(properlyInitialized(), "Job is not properly initialized");
}

JobPrint::~JobPrint() {}
