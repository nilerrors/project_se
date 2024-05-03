//
// Created by student on 2/05/24.
//

#include "JobBlackWhite.h"

JobBlackWhite::JobBlackWhite(int jobNumber, int pageCount, const std::string &userName) : JobPrint(jobNumber, pageCount,
                                                                                              userName) {

}

JobBlackWhite::~JobBlackWhite() {}

std::string JobBlackWhite::getType() {
    return "black-and-white job";
}
