//
// Created by nilerrors on 5/1/24.
//

#ifndef PRINTSYSTEM_REPORTER_H
#define PRINTSYSTEM_REPORTER_H

#include <string>
#include <vector>

class Device;
class Job;

class Reporter {
public:
    /**
     * \brief Constructor for Reporter
     */
    Reporter();

    /**
     * \brief Generates a report for a device
     * @param device

     * @require
			- REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
			- REQUIRE(device != NULL, "Device should not be NULL");
			- REQUIRE(device->getEmission() >= 0, "Emission is negative.");
			- REQUIRE(device->getSpeed() >= 0, "Speed is negative.");
			- REQUIRE(device->getCost() >=0, "Cost is negative");
			- REQUIRE(isValidDeviceType_2(PrintingTypeToDeviceString(device->getType())), "Type is not defined");

     * @ensure
            - ENSURE(!report.empty(), "Device report is empty");
     */
    virtual void generateDeviceReport(Device *const device);

    /**
     * \brief Generates a report for a job
     * @param job

     * @require
			- REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
			- REQUIRE(job->getJobNumber() >= 0, "JobNumber is negative.");
			- REQUIRE(job->getPageCount() >= 0, "PageCount is negative.");
			- REQUIRE(job->getPrintedPageCount() >=0, "PrintedPageCount is negative");
			- REQUIRE(isValidJobType(PrintingTypeToJobString(job->getType())), "Type is not defined");
			- REQUIRE(job->getAssignedTo() != NULL, "Device should be assigned");

     * @ensure
            - ENSURE(!report.empty(), "Job report is empty");
     */
    virtual void generateJobReport(Job *const job);

    /**
     * \brief Generates a report for the finish of a job
     * @param job

     * @require
			- REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
			- REQUIRE(job != NULL, "Job should not be NULL");
			- REQUIRE(job->getAssignedTo() != NULL, "Job is not assigned to a device");

     * @ensure
            - ENSURE(!report.empty(), "Job report is empty");
     */
    virtual void generateJobFinishReport(Job *const job);

    /**
     * \brief Generates an advanced report about the device
     * @param device

     * @require
			- REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
			- REQUIRE(device != NULL, "Device should not be NULL");

     * @ensure
            - ENSURE(!report.empty(), "Advance Device report is empty");
     */
    virtual void generateDeviceAdvancedReport(Device *const device);

    /**
     * \brief Generates an advanced report about the job
     * @param devices, jobs

     * @require
            - REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
            - REQUIRE(report.empty(), "Report should be empty");

     * @ensure
            - ENSURE(!report.empty(), "Advance Job report is empty");
     */
    virtual void generateSystemStatus(const std::vector<Device *> &devices, const std::vector<Job *> &jobs);

    /**
     * \brief Get the report
     * @return

     * @require
            - REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
     */
    std::string getReport() const;

    /**
     * \brief Clears the report

     * @require
            - REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");

     * @ensure
            - ENSURE(report == "", "Report should be empty");
     */
    void clearReport();

    /**
     * \brief Checks if the class is properly initialized
     * @return True if the class is properly

     * @ensure
            - ENSURE(properlyInitialized(), "Reporter should be properlyInitialized");
     */
    void toFile(const std::string &file_name) const;

private:
    bool properlyInitialized() const { return _init == this; }

private:
    Reporter *_init;
    std::string report;
};


#endif //PRINTSYSTEM_REPORTER_H
