//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBCOLOR_H
#define PRINTSYSTEM_JOBCOLOR_H

#include "JobPrint.h"
#include "lib/DesignByContract.h"

class JobColor : public JobPrint {
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
    JobColor(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
    ~JobColor() override;

    /**
     * \brief Get type of device
     * @return

     * @ensure
        - REQUIRE(properlyInitialized(), "JobColor is not properly initialized");
     */
    std::string getType() override;

    /**
     * \brief Get the compatible device type
     * @return

     * @ensure
        - REQUIRE(properlyInitialized(), "JobColor is not properly initialized");
     */
    std::string getCompatiblDeviceType() override {
        REQUIRE(properlyInitialized(), "JobBlackWhite is not properly initialized");
        return "Color printer";
    }
};


#endif //PRINTSYSTEM_JOBCOLOR_H
