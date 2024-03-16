//
// Created by student on 29/02/24.
//

#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H

#include <string>

#include "tinyxml.h"

class Device;

class Job {
public:
    Job(TiXmlElement *job_element);

    Job(int jobNumber, int pageCount, const std::string &userName);

	bool properlyInitialized() const { return init_ == this; }

    int getJobNumber() const;

    int getPageCount() const;

    const std::string &getUserName() const;

	bool isFinished() const;

	bool isInProcess() const;

	void setInProcess(bool inProcess);

	void setFinished(bool finished);

	Device *getAssignedTo() const;

	void setAssignedTo(Device *assignedTo);

	std::string finishMessage() const;

private:
	bool finished = false;
	bool inProcess = false;
	Device *assignedTo = NULL;
    int jobNumber;
    int pageCount;
    std::string userName;
	Job *init_;
};


#endif //PROJECTTITLE_JOB_H
