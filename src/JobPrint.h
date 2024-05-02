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
     * \param device_element TiXmlElement containing the device data
     * \return A new Job object

     * @expect
        - EXPECT(!temp_jobNumber.empty(), "No job number is provided");
        - EXPECT(!temp_pageCount.empty(), "No page count is provided");
        - EXPECT(is_number(temp_jobNumber) , "Job number should be a number");
        - EXPECT(is_number(temp_pageCount) , "Page count should be a number");
        - EXPECT(!temp_userName.empty(), "No user name is provided");
     */
    JobPrint(TiXmlElement *job_element);

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

    std::string getType() override = 0;
};


#endif //PRINTSYSTEM_JOBPRINT_H
