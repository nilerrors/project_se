//
// Created by nilerrors on 4/12/24.
//

#ifndef PRINTSYSTEM_CONSTS_H
#define PRINTSYSTEM_CONSTS_H

#include <string>

enum PrintingType
{
    bw,
    color,
    scan
};


PrintingType StringToPrintingType(const std::string &typstr);
std::string PrintingTypeToDeviceString(PrintingType type);
std::string PrintingTypeToJobString(PrintingType type);

#endif //PRINTSYSTEM_CONSTS_H
