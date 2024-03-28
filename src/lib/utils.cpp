//
// Created by student on 29/02/24.
//

//============================================================================
// Source      : https://github.com/sergedemeyer/TicTacToe_Git/blob/master/TicTacToeUtils.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : utils in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <chrono>
#include <sstream>
#include <random>
#include <iomanip>

using namespace std;

#include "utils.h"

/**
Auxiliary functions for file manipulation.
*/
bool DirectoryExists(const std::string dirname) {
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

bool FileExists(const std::string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) return false;
    ifstream f(filename);
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

bool FileIsEmpty(const std::string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) return true; // File does not exist; thus it is empty
    return st.st_size == 0;
}

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
    ifstream leftFile, rightFile;
    char leftRead, rightRead;
    bool result;

    // Open the two files.
    leftFile.open(leftFileName);
    if (!leftFile.is_open()) {
        return false;
    };
    rightFile.open(rightFileName);
    if (!rightFile.is_open()) {
        leftFile.close();
        return false;
    };

    result = true; // files exist and are open; assume equality unless a counterexamples shows up.
    while (result && leftFile.good() && rightFile.good()) {
        leftFile.get(leftRead);
        rightFile.get(rightRead);
        result = (leftRead == rightRead);
    };
    if (result) {
        // last read was still equal; are we at the end of both files ?
        result = (!leftFile.good()) && (!rightFile.good());
    };

    leftFile.close();
    rightFile.close();
    return result;
}

bool StringCompare(const std::string &leftString, const std::string &rightString) {
	return leftString == rightString;
}

// Source: https://stackoverflow.com/a/4654718
bool is_number(const std::string& s)
{
    if (s.empty())
        return false;

    std::string::const_iterator it = s.begin();

    if (*it == '-') {
        ++it;

        if (it == s.end())
            return false;
    }

    while (it != s.end() && std::isdigit(*it))
        ++it;

    return it == s.end();
}


std::string GenerateFileName(const std::string &prefix, const std::string &extension)
{
	time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;

	// random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 99);
	int random_number = dis(gen);

    ss << std::put_time(std::localtime(&now), "%Y-%m-%d-%H%M%S") << "-" << random_number;

	return prefix + ss.str() + extension;
}

bool isValidDeviceType(const string &typeStr) {
    return (typeStr == "bw" || typeStr == "color" || typeStr == "scan");
}

