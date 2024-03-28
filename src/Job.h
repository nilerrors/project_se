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
    enum types {bw, color, scan};

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

	bool properlyInitialized() const { return init_ == this; }

	/**
	 * \brief Gets the job number
	 * @return
	 */
    int getJobNumber() const;

	/**
	 * \brief Gets the page count
	 * @return
	 */
    int getPageCount() const;

	/**
	 * \brief Gets the user name
	 * @return
	 */
    const std::string &getUserName() const;

	/**
	 * \brief Checks if the job is finished
	 * @return
	 */
	bool isFinished() const;

	/**
	 * \brief Checks if the job is in process
	 * @return
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
	 * @return
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

    static Job::types stringtoType(std::string &typstr);

private:
	bool finished = false;
	bool inProcess = false;
	Device *assignedTo = NULL;
    int jobNumber;
    int pageCount;
    types type;
    std::string userName;
	Job *init_;
};


#endif //PROJECTTITLE_JOB_H
