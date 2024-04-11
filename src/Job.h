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
    enum JobTypes {bw, color, scan};
    enum Status {unassigned, waiting, printing, done};

	/**
	 * \brief Constructor for Job
	 * \param device_element TiXmlElement containing the device data
	 * \return A new Job object

	 * @expect
		- EXPECT(!temp_jobNumber.empty(), "No job number is provided");
		- EXPECT(!temp_pageCount.empty(), "No page count is provided");
		- EXPECT(is_number(temp_jobNumber) , "Job number should be a number");
		- EXPECT(is_number(temp_pageCount) , "Page count should be a number");
		- EXPECT(!temp_userName.empty(), "No user name is provided");
	 */
    Job(TiXmlElement *job_element);

	/**
	 * \brief Constructor for Job
	 * @param jobNumber
	 * @param pageCount
	 * @param userName
	 */
    Job(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Checks if the class is properly
     * @return A boolean indicating if the class is properly initialized
     */
	bool properlyInitialized() const { return init_ == this; }

	/**
	 * \brief Gets the job number
	 * @return job number
	 */
    int getJobNumber() const;

	/**
	 * \brief Gets the page count
	 * @return page count
	 */
    int getPageCount() const;

	/**
	 * \brief Gets the user name
	 * @return userName
	 */
    const std::string &getUserName() const;

    /**
     * \brief Get job status
     * @return Status
     */
     Status getStatus() const;

        /**
         * \brief Get printed page count
         * @return printed page count
         */

     int getPrintedPageCount() const;

	/**
	 * \brief Checks if the job is finished
	 * @return A boolean indicating if the job is finished
	 */
	bool isFinished() const;

	/**
	 * \brief Checks if the job is in process
	 * @return A boolean indicating if the job is in process
	 */
	bool isInProcess() const;

	/**
	 * \brief Sets the job to in process
	 * @param inProcess
	 */
	void setInProcess(bool inProcess);

	/**
	 * \brief Sets the job to finished
	 * @param finished
	 */
	void setFinished(bool finished);

	/**
	 * \brief Gets the device the job is assigned to
	 * @return assignedTo
	 */
	Device *getAssignedTo() const;

	/**
	 * \brief Sets the device the job is assigned to
	 * @param assignedTo
	 */
	void setAssignedTo(Device *assignedTo);

	/**
	 * \brief Returns a string containing the finish message
	 * \return A string containing the finish message

	 * @require
		- REQUIRE(properlyInitialized(), "Job is not properly initialized");
		- REQUIRE(assignedTo != NULL, "Job is not assigned to a device");
	 */
	std::string finishMessage() const;

    /**
     * \brief Converts the string representation of the job type to it's enum value
     * @param typstr
     * @return JobTypes
     */
    static Job::JobTypes stringtoType(std::string &typstr);

    /**
	 * \brief Prints a report of the job
	 * \return A string containing the report

	 * @require
		- REQUIRE(properlyInitialized(), "Class is not properly initialized.");
        - REQUIRE(jobNumber >= 0, "Job number is negative.");
        - REQUIRE(pageCount >= 0, "Page count is negative.");
        - REQUIRE(printedPageCount>=0, "Printed page count is negative");
        - REQUIRE(isValidJobType(job_type_to_string(type)), "Type is not defined");

	 * @ensure
		- ENSURE(result != "", "Report is empty.");
	 */
    std::string printReport() const;



    /**
     * \brief Converts the given job type to string representation
     * @param job_type
     * @return string
     */

    static std::string job_type_to_string(JobTypes job_type);



    /**
     * \brief Get position in queue
     * @return queue number
     */

    int getQueueNumber() const;

private:
    Status status = Status::unassigned;
	Device *assignedTo = NULL;
    int jobNumber;
    int pageCount;
    int printedPageCount;
    JobTypes type;
    std::string userName;
	Job *init_;
};


#endif //PROJECTTITLE_JOB_H
