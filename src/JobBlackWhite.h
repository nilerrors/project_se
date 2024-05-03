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
     */
    JobBlackWhite(int jobNumber, int pageCount, const std::string &userName);

    /**
     * \brief Destructor for Job
     */
    ~JobBlackWhite() override;

    std::string getType() override;

    std::string getCompatiblDeviceType() override {
        return "Black-and-white printer";
    }
};


#endif //PRINTSYSTEM_JOBBLACKWHITE_H
