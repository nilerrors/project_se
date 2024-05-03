//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_JOBFACTORY_H
#define PRINTSYSTEM_JOBFACTORY_H

#include "Job.h"

class JobFactory {
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

     * @ensure
        - ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     */
    explicit JobFactory(TiXmlElement *job_element);

    /**
     * \brief Get the job
     * @return

     * @require
        - REQUIRE(properlyInitialized(), "JobFactory is not properly initialized");
     */
    Job *getJob() const;

private:
    /**
     * \brief Checks if the class is properly
     * @return A boolean indicating if the class is properly initialized
     */
    bool properlyInitialized() const { return init_ == this; }

private:
    Job *job = nullptr;
    JobFactory *init_ = nullptr;
};


#endif //PRINTSYSTEM_JOBFACTORY_H
