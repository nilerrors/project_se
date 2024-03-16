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

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);

bool is_number(const std::string& s);

std::string GenerateFileName(const std::string &prefix, const std::string &extension);

#endif //PROJECTTITLE_UTILS_H
