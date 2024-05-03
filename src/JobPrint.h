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
     */
    JobPrint(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
    ~JobPrint() override;
};


#endif //PRINTSYSTEM_JOBPRINT_H
