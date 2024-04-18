//
// Created by student on 29/02/24.
//

#ifndef PROJECTTITLE_UTILS_H
#define PROJECTTITLE_UTILS_H

//============================================================================
// Source      : https://github.com/sergedemeyer/TicTacToe_Git/blob/master/TicTacToeUtils.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : utils in C++, Ansi-style
//============================================================================


#include <iostream>

/**
 * \brief Checks if a directory exists
 * @param dirname
 * @return true if the directory exists
 */
bool DirectoryExists(const std::string dirname);

/**
 * \brief Checks if a file exists
 * @param dirname
 * @return true if the file exists
 */
bool FileExists(const std::string dirname);

/**
 * \brief Checks if a file is empty
 * @param filename
 * @return true if the file is empty
 */
bool FileIsEmpty(const std::string filename);

/**
 * \brief Compares two files
 * @param leftFileName
 * @param rightFileName
 * @return true if the files are the same
 */
bool FileCompare(const std::string leftFileName, const std::string rightFileName);

/**
 * \brief Compares two strings
 * @param left
 * @param right
 * @return true if the strings are the same
 */
bool StringCompare(const std::string &left, const std::string &right);

/**
 * \brief Checks if a string is a number
 * @param s
 * @return true if the string is a number
 */
bool is_number(const std::string& s);

/**
 * \brief Generates a file name
 * @param prefix
 * @param extension
 * @return the generated file name
 */
std::string GenerateFileName(const std::string &prefix, const std::string &extension);

/**
 * \brief Checks if the given string is a valid device type.
 * @param typeStr
 * @return
 */
bool isValidDeviceType(const std::string& typeStr);

/**
 * \brief Checks if the given string is a valid device type. This function is called when print report is getting called and is used to check if the type is valid.
 * @param typeStr
 * @return
 */
bool isValidDeviceType_2(const std::string &typeStr);

bool isValidJobType(const std::string &typeStr);




#endif //PROJECTTITLE_UTILS_H
