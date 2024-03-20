//
// Created by nilerrors on 3/20/24.
//

#ifndef PRINTSYSTEM_LOGGER_H
#define PRINTSYSTEM_LOGGER_H

#include <string>

class Logger
{
public:
	Logger() = default;
	virtual ~Logger() = default;

	virtual void log(const std::string &message) {}
	virtual void error(const std::string &message) {}
};

class FileLogger : public Logger
{
public:
	explicit FileLogger(const std::string &file_name, bool append = true) : file_name(file_name), append(append) {}
	~FileLogger() override = default;

	void log(const std::string &message) override;

	void error(const std::string &message) override;

	void setFileName(const std::string &filename, bool add = true) {
		file_name = filename;
		append = add;
	}

private:
	std::string file_name;
	bool append;
};

class ConsoleLogger : public Logger
{
public:
	ConsoleLogger() = default;
	~ConsoleLogger() override = default;

	void log(const std::string &message) override;
	void error(const std::string &message) override;
};


class StringLogger : public Logger
{
public:
	StringLogger() = default;
	explicit StringLogger(std::string *log, bool append = false) : logged(log), append(append) {}
	~StringLogger() override = default;

	void log(const std::string &message) override {
		if (append)
			*logged += message + "\n";
		else
			*logged = message + "\n";
	}

	void error(const std::string &message) override {
		if (append)
			*logged += "ERROR: " + message + "\n";
		else
			*logged = "ERROR: " + message + "\n";
	}

	void setString(std::string *log) {
		logged = log;
	}

private:
	std::string *logged;
	bool append;
};


#endif //PRINTSYSTEM_LOGGER_H
