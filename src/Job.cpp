//
// Created by student on 29/02/24.
//

#include "Job.h"

Job::Job(int jobNumber, int pageCount, const std::string &userName) : jobNumber(jobNumber), pageCount(pageCount),
                                                                      userName(userName) {}

Job::Job(TiXmlElement job_element) {

}
