//
// Created by student on 29/02/24.
//

#ifndef PROJECTTITLE_DEVICE_H
#define PROJECTTITLE_DEVICE_H

#include <string>
#include <deque>
#include "tinyxml.h"

class Job;

class Device
{
public:
	/**
	 * \brief Constructor for Device
	 * \param device_element TiXmlElement containing the device data
	 * \return A new Device object

	 * @expect
		- EXPECT(!temp_name.empty(), "No name is provided");
		- EXPECT(!temp_emission.empty(), "No emission is provided");
		- EXPECT(is_number(temp_emission) , "Emission should be an integer number");
		- EXPECT(!temp_speed.empty(), "No speed is provided");
		- EXPECT(is_number(temp_speed) , "Speed should be an integer number");
	 */
    explicit Device(TiXmlElement *device_element);

    Device(const std::string &name, int emission, int speed);

	bool properlyInitialized() const { return init_ == this; }

    const std::string &getName() const;

    int getEmission() const;

    int getSpeed() const;

	/**
	 * brief Adds a job to the device
	 * \param job Job to be added

	 * @require
	    - REQUIRE(properlyInitialized(), "Class is not properly initialized.");
		- REQUIRE(job != NULL, "Job is empty.");

	 * @ensure
		- ENSURE(jobs.back() == job, "Job is not added to the device.");
	 */
	void addJob(Job *job);

	/**
	 * \brief Prints a report of the device
	 * \return A string containing the report

	 * @require
		- REQUIRE(properlyInitialized(), "Class is not properly initialized.");
		- REQUIRE(emission >= 0, "Emission is negative.");
		- REQUIRE(speed >= 0, "Speed is negative.");

	 * @ensure
		- ENSURE(result != "", "Report is empty.");
	 */
	std::string printReport() const;

	/**
	 * \brief Gets the load of the device
	 * \return The load of the device

	 * @require
		- REQUIRE(properlyInitialized(), "Class is not properly initialized.");

	 * @ensure
		- ENSURE(result >= 0, "Load is negative.");
	 */
	int getLoad() const;

	/**
	 * \brief Processes a job
	 * \return A string containing the result of the processing

	 * @require
		- REQUIRE(properlyInitialized(), "Class is not properly initialized.");
		- REQUIRE(!jobs.empty(), "No jobs to process.");
		- REQUIRE(jobs.front() != NULL, "First job is empty");

	 * @ensure
		- ENSURE(jobs.front() != job, "Job is not removed");
		- ENSURE(job->isFinished(), "Job is not finished.");
	 */
	std::string processJob();

private:
    Device *init_;
    std::string name;
    int emission;
    int speed;
	std::deque<Job *> jobs;
};


#endif //PROJECTTITLE_DEVICE_H
