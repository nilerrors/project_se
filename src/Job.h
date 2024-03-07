//
// Created by student on 29/02/24.
//

#ifndef PROJECTTITLE_JOB_H
#define PROJECTTITLE_JOB_H

#include <string>

#include "tinyxml.h"

class Job {
public:
    Job(TiXmlElement *job_element);

    Job(int jobNumber, int pageCount, const std::string &userName);

	bool properlyInitialized() const { return init_ == this; }

    int getJobNumber() const;

    int getPageCount() const;

    const std::string &getUserName() const;

private:
    int jobNumber;
    int pageCount;
    std::string userName;
	Job *init_;
};


#endif //PROJECTTITLE_JOB_H
