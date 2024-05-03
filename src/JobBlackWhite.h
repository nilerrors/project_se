//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBBLACKWHITE_H
#define PRINTSYSTEM_JOBBLACKWHITE_H

#include "JobPrint.h"

class JobBlackWhite : public JobPrint {
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
    JobBlackWhite(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
    ~JobBlackWhite() override;

    /**
     * \brief Get type of device
     * @return

     * @ensure
        - REQUIRE(properlyInitialized(), "JobBlackWhite is not properly initialized");
     */
    std::string getType() override;

    /**
     * \brief Get the compatible device type
     * @return

     * @ensure
        - REQUIRE(properlyInitialized(), "JobBlackWhite is not properly initialized");
     */
    std::string getCompatiblDeviceType() override {
        REQUIRE(properlyInitialized(), "JobBlackWhite is not properly initialized");
        return "Black-and-white printer";
    }
};


#endif //PRINTSYSTEM_JOBBLACKWHITE_H
