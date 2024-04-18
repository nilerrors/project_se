//
// Created by nilerrors on 3/20/24.
//

#include <fstream>
#include <iostream>
#include "Logger.h"

void FileLogger::log(const std::string &message)
{
	std::ofstream file;
	if (append)
	{
		file.open(file_name, std::ios_base::app);
	}
	else
	{
		file.open(file_name);
	}
	file << message << std::endl;
	file.close();
}

void FileLogger::error(const std::string &message)
{
	std::ofstream file;
	if (append)
	{
		file.open(file_name, std::ios_base::app);
	}
	else
	{
		file.open(file_name);
	}
	file << "ERROR: " << message << std::endl;
	file.close();
}

void ConsoleLogger::log(const std::string &message)
{
	std::cout << message << std::endl;
}

void ConsoleLogger::error(const std::string &message)
{
	std::cerr << message << std::endl;
}
