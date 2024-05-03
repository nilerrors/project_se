//
// Created by student on 2/05/24.
//

#include "JobColor.h"

JobColor::JobColor(int jobNumber, int pageCount, const std::string &userName) : JobPrint(jobNumber, pageCount, userName) {

}

JobColor::~JobColor() {

}

std::string JobColor::getType() {
    return "color-printing job";
}
