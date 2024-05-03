//
// Created by student on 2/05/24.
//

#include "JobPrint.h"

JobPrint::JobPrint(TiXmlElement *job_element) : Job(job_element) {}

JobPrint::JobPrint(int jobNumber, int pageCount, const std::string &userName) : Job(jobNumber, pageCount, userName) {}

JobPrint::~JobPrint() {}
