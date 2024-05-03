//
// Created by student on 29/02/24.
//

#include "lib/DesignByContract.h"
#include "Device.h"
#include "lib/utils.h"
#include "System.h"
#include "Reporter.h"
#include <iostream>
#include <sstream>

Device::Device(const std::string &name, int emission, int speed, int cost)
        : init_(this), name(name), emission(emission), speed(speed), cost(cost) {}

const std::string &Device::getName() const {
    return name;
}

int Device::getEmission() const {
    return emission;
}

int Device::getSpeed() const {
    return speed;
}

void Device::addJob(Job *job)
{
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	REQUIRE(job != NULL, "Job is empty.");
    job->setAssignedTo(this);
	jobs.push_back(job);
	ENSURE(jobs.back() == job, "Job is not added to the device.");
}

int Device::getLoad() const
{
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	int load = 0;
	for (Job *job : jobs)
	{
		load += job->getPageCount();
	}
	ENSURE(load >= 0, "Load is negative.");
	return load;
}

std::string Device::processJob()
{
	REQUIRE(properlyInitialized(), "Class is not properly initialized.");
	REQUIRE(!jobs.empty(), "No jobs to process.");
	REQUIRE(jobs.front() != NULL, "First job is empty");

    Reporter reporter;
	Job *job = jobs.front();

    assert(job->getStatus() != Job::done);  // cannot process finished job

    job->setStatus(Job::printing);
    job->increasePrintedPageCount();
    if (job->getPrintedPageCount() == job->getPageCount())
    {
        job->setStatus(Job::done);
        jobs.pop_front();
        ENSURE(jobs.front() != job, "Job is not removed");
        ENSURE(job->getStatus() == Job::done, "Job is not finished.");
        reporter.generateJobFinishReport(job);
    }

	return reporter.getReport();
}

int Device::getCost() const {
    return cost;
}

std::deque<Job *> Device::getJobs() const {
    return jobs;
}

//PrintingType Device::getType() const {
//    return type;
//}


