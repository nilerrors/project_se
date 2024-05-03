//
// Created by student on 29/02/24.
//

#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H

#include <string>
#include "lib/tinyxml.h"

class Device;

class Job {
public:
    enum Status {unassigned, assigned, waiting, printing, done};

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
	 */
    Job(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
     virtual ~Job() = default;

    /**
     * \brief Checks if the class is properly
     * @return A boolean indicating if the class is properly initialized
     */
	bool properlyInitialized() const { return init_ == this; }

	/**
	 * \brief Gets the job number
	 * @return job number

	 * @ensure
	    - REQUIRE(properlyInitialized(), "Job is not properly initialized");
	 */
    int getJobNumber() const;

	/**
	 * \brief Gets the page count
	 * @return page count

	 * @ensure
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
	 */
    int getPageCount() const;

	/**
	 * \brief Gets the user name
	 * @return userName

	 * @ensure
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
	 */
    const std::string &getUserName() const;

    /**
     * \brief Get job status
     * @return Status

     * @ensure
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
     */
    Status getStatus() const;

    /**
    * \brief Sets the job status
    * @return

    * @require
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");

    * @ensure
        - ENSURE(status == stat, "Status is not set correctly")
    */
    void setStatus(Status stat);

    /**
     * \brief Get printed page count
     * @return printed page count

    * @ensure
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
     */
    int getPrintedPageCount() const;

    /**
    * \brief Incease printed page count
    * @return

    * @require
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
        - REQUIRE(printedPageCount < pageCount, "Printed page count should be less than total page count");

    * @ensure
        - ENSURE(printedPageCount <= pageCount, "Printed page count should be less than total page count");
    */
    void increasePrintedPageCount();

	/**
	 * \brief Gets the device the job is assigned to
	 * @return assignedTo

	 * @require
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
	 */
	Device *getAssignedTo() const;

	/**
	 * \brief Sets the device the job is assigned to
	 * @param assignedTo
	 * @require
	   - REQUIRE(properlyInitialized(), "Job is not properly initialized");
	   - REQUIRE(assigned != NULL, "Job is not assigned to a device");
	 * @ensure
	   - ENSURE(assignedTo == assigned, "Device is not assigned correctly");
	 */
	void setAssignedTo(Device *assignedTo);

    /**
     * \brief Get type of job
     * @return
     */
    virtual std::string getType() = 0;

    /**
     * \brief Get the compatible device type
     * @return compatible device

     * @require
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
     */
     virtual std::string getCompatiblDeviceType() = 0;

    /**
     * \brief Get position in queue
     * @return queue number

     * @require
        - REQUIRE(properlyInitialized(), "Job is not properly initialized");
        - REQUIRE(getAssignedTo() != NULL, "Job is not assigned to a device");
     */
    int getQueueNumber() const;

private:
    Job *init_;
    Status status = Status::unassigned;
	Device *assignedTo = NULL;
    int jobNumber;
    int pageCount;
    int printedPageCount = 0;
    std::string userName;
};


#endif //PROJECTTITLE_JOB_H
