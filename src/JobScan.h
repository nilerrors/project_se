//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBSCAN_H
#define PRINTSYSTEM_JOBSCAN_H

#include "lib/DesignByContract.h"
#include "Job.h"

class JobScan : public Job {
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
    JobScan(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
    ~JobScan() override;

    /**
     * \brief Get type of device
     * @return

     * @ensure
        - REQUIRE(properlyInitialized(), "JobScan is not properly initialized");
     */
    std::string getType() override;

    /**
     * \brief Get the compatible device type
     * @return

     * @ensure
        - REQUIRE(properlyInitialized(), "JobScan is not properly initialized");
     */
    std::string getCompatiblDeviceType() override {
        REQUIRE(properlyInitialized(), "JobScan is not properly initialized");
        return "Scanner";
    }
};


#endif //PRINTSYSTEM_JOBSCAN_H
