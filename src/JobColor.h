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
     * \param device_element TiXmlElement containing the device data
     * \return A new Job object

     * @expect
        - EXPECT(!temp_jobNumber.empty(), "No job number is provided");
        - EXPECT(!temp_pageCount.empty(), "No page count is provided");
        - EXPECT(is_number(temp_jobNumber) , "Job number should be a number");
        - EXPECT(is_number(temp_pageCount) , "Page count should be a number");
        - EXPECT(!temp_userName.empty(), "No user name is provided");
     */
    explicit JobColor(TiXmlElement *job_element);

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
};


#endif //PRINTSYSTEM_JOBCOLOR_H
