//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBCOLOR_H
#define PRINTSYSTEM_JOBCOLOR_H

#include "JobPrint.h"

class JobColor : public JobPrint {
public:
    /**
     * \brief Constructor for Job
     * @param jobNumber
     * @param pageCount
     * @param userName
     */
    JobColor(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
    ~JobColor() override;

    std::string getType() override;

    std::string getCompatiblDeviceType() override {
        return "Color printer";
    }
};


#endif //PRINTSYSTEM_JOBCOLOR_H
