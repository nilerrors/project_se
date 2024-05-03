//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBSCAN_H
#define PRINTSYSTEM_JOBSCAN_H

#include "Job.h"

class JobScan : public Job {
public:
    /**
     * \brief Constructor for Job
     * @param jobNumber
     * @param pageCount
     * @param userName
     */
    JobScan(int jobNumber, int pageCount, const std::string &userName);

    ~JobScan() override;

    std::string getType() override;

    std::string getCompatiblDeviceType() override {
        return "Scanner";
    }
};


#endif //PRINTSYSTEM_JOBSCAN_H
