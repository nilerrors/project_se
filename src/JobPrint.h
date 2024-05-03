//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBPRINT_H
#define PRINTSYSTEM_JOBPRINT_H

#include "Job.h"

class JobPrint : public Job {
public:
    /**
     * \brief Constructor for Job
     * @param jobNumber
     * @param pageCount
     * @param userName

     * @ensure
		- ENSURE(getJobNumber() == jobNumber, "Job number is not set correctly");
		- ENSURE(getPageCount() == pageCount, "Page count is not set correctly");
		- ENSURE(getUserName() == userName, "User name is not set correctly");
		- ENSURE(getStatus() == Status::unassigned, "Status is not set correctly");
		- ENSURE(getPrintedPageCount() == 0, "Printed page count is not set correctly");
		- ENSURE(properlyInitialized(), "Job is not properly initialized");
     */
    JobPrint(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
    ~JobPrint() override;
};


#endif //PRINTSYSTEM_JOBPRINT_H
