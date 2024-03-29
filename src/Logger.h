//
// Created by nilerrors on 3/20/24.
//

#ifndef PRINTSYSTEM_LOGGER_H
#define PRINTSYSTEM_LOGGER_H

#include <string>

class Logger
{
public:
    /**
     * \brief Constructor of Logger
     */
	Logger() = default;

    /**
     * \brief Destructor of FileLogger
     */
	virtual ~Logger() = default;

    /**
     * \brief Logs the given message.
     * @param message
     */
	virtual void log(const std::string &message) {}

    /**
     * \brief Logs the given error message.
     * @see Logger::log
     * @param message
     */
	virtual void error(const std::string &message) {}
};

class FileLogger : public Logger
{
public:
    /**
     * \brief Constructor of FileLogger
     * @param file_name
     * @param append
     */
	explicit FileLogger(const std::string &file_name, bool append = true) : file_name(file_name), append(append) {}

    /**
     * \brief Destructor of FileLogger
     */
	~FileLogger() override = default;

    /**
     * \brief Logs the given message to a file. Appends to the file if the append option is selected.
     * @param message
     */
	void log(const std::string &message) override;

    /**
     * \brief Logs an error to the file.
     * @see FileLogger::log
     * @param message
     */
	void error(const std::string &message) override;

    /**
     * \brief Sets the name of the file to write to.
     * @param filename
     * @param add option to append to the file
     */
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
    /**
     * \brief Constructor of ConsoleLogger
     */
	ConsoleLogger() = default;

    /**
     * \brief Destructor of ConsoleLogger
     */
	~ConsoleLogger() override = default;

    /**
     * \brief Logs the given message to the console.
     * @param message
     */
	void log(const std::string &message) override;

    /**
     * \brief Logs the given error to the console.
     * @see ConsoleLogger::log
     * @param message
     */
	void error(const std::string &message) override;
};


class StringLogger : public Logger
{
public:
    /**
     * \brief Constructor of StringLogger
     */
	StringLogger() = default;

    /**
     * \brief Constructor of StringLogger
     * @param log
     * @param append
     */
	explicit StringLogger(std::string *log, bool append = false) : logged(log), append(append) {}

    /**
     * \brief Destructor of StringLogger
     */
	~StringLogger() override = default;

    /**
     * \brief Logs the given message to the string. Appends to the string if the append option is selected.
     * @param message
     */
	void log(const std::string &message) override {
		if (append)
			*logged += message + "\n";
		else
			*logged = message + "\n";
	}

    /**
     * \brief Logs the given error to the string.
     * @see StringLogger::log
     * @param message
     */
	void error(const std::string &message) override {
		if (append)
			*logged += "ERROR: " + message + "\n";
		else
			*logged = "ERROR: " + message + "\n";
	}

    /**
     * \brief Sets the address of the string to log to.
     * @param log
     */
	void setString(std::string *log) {
		logged = log;
	}

private:
	std::string *logged;
	bool append;
};


#endif //PRINTSYSTEM_LOGGER_H
