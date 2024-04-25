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


/**
 * @brief Converts a string to a PrintingType
 * @param typstr
 * @return
 */
PrintingType StringToPrintingType(const std::string &typstr);

/**
 * @brief Converts a PrintingType to a string for a device
 * @param type
 * @return
 */
std::string PrintingTypeToDeviceString(PrintingType type);

/**
 * @brief Converts a PrintingType to a string for a job
 * @param type
 * @return
 */
std::string PrintingTypeToJobString(PrintingType type);

#endif //PRINTSYSTEM_CONSTS_H
