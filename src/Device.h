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
    explicit Device(TiXmlElement *device_element);

    Device(const std::string &name, int emission, int speed);

	bool properlyInitialized() const { return init_ == this; }

    const std::string &getName() const;

    int getEmission() const;

    int getSpeed() const;

	void addJob(Job *job);

	std::string printReport() const;

	int getLoad() const;

	std::string processJob();

private:
    Device *init_;
    std::string name;
    int emission;
    int speed;
	std::deque<Job *> jobs;
};


#endif //PROJECTTITLE_DEVICE_H
