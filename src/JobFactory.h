//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBFACTORY_H
#define PRINTSYSTEM_JOBFACTORY_H

#include "Job.h"

class JobFactory {
public:
    explicit JobFactory(TiXmlElement *job_element);

    Job *getJob() const;

private:
    Job *job = nullptr;
};


#endif //PRINTSYSTEM_JOBFACTORY_H
