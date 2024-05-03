//
// Created by student on 2/05/24.
//

#include "JobColor.h"

JobColor::JobColor(TiXmlElement *job_element) : JobPrint(job_element) {

}

JobColor::JobColor(int jobNumber, int pageCount, const std::string &userName) : JobPrint(jobNumber, pageCount, userName) {

}

JobColor::~JobColor() {

}

std::string JobColor::getType() {
    return "color-printing job";
}
