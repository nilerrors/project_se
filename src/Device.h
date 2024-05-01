//
// Created by student on 29/02/24.
//

#ifndef PROJECTTITLE_DEVICE_H
#define PROJECTTITLE_DEVICE_H

#include <string>
#include <deque>
#include "lib/tinyxml.h"
#include "Consts.h"

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

	/**
	 * \brief Constructor for Device
	 * @param name
	 * @param emission
	 * @param speed
	 */
    Device(const std::string &name, int emission, int speed);

	/**
	 * \brief Checks if the class is properly
	 * @return A boolean indicating if the class is properly
	 */
	bool properlyInitialized() const { return init_ == this; }

    PrintingType getType() const;

    /**
     * \brief Gets the name of the device
     * @return name
     */
    const std::string &getName() const;

	/**
	 * \brief Gets the emission of the device
	 * @return emmission
	 */
    int getEmission() const;

	/**
	 * \brief Gets the speed of the device
	 * @return speed
     */

    int getSpeed() const;


    /**
     * \brief Gets the cost of the device
     * @return cost
     */
    int getCost() const;


    /**
     * \brief Gets the jobs of the device
     * @return A deque containing the jobs
     */

    std::deque<Job *> getJobs() const;

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
	 * \brief Gets the load of the device
	 * \return The load of the device

	 * @require
		- REQUIRE(properlyInitialized(), "Class is not properly initialized.");

	 * @ensure
		- ENSURE(result >= 0, "Load is negative.");
	 */
	int getLoad() const;

	/**
	 * \brief Prints a single page of a job
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
    int cost;
    PrintingType type;
	std::deque<Job *> jobs;
};


#endif //PROJECTTITLE_DEVICE_H
