//
// Created by nilerrors on 5/1/24.
//

#include "lib/DesignByContract.h"
#include "lib/utils.h"
#include "Device.h"
#include "Job.h"
#include "Reporter.h"

Reporter::Reporter() : _init(this) {}

void Reporter::generateDeviceReport(Device *const device) {
    REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
    REQUIRE(device != NULL, "Device should not be NULL");
    REQUIRE(report.empty(), "Report should be empty");
    REQUIRE(device->getEmission() >= 0, "Emission is negative.");
    REQUIRE(device->getSpeed() >= 0, "Speed is negative.");
    REQUIRE(device->getCost() >=0, "Cost is negative");
    REQUIRE(isValidDeviceType_2(device->getType()), "Type is not defined");

    report += device->getName() + ":\n";
    report += "* CO2: " + std::to_string(device->getEmission()) + "g/page\n";
    report += "* " + std::to_string(device->getSpeed()) + " pages / minute\n";
    report += "* " + device->getType() + "\n";
    report += "* " + std::to_string(device->getCost()) + " cents / page";
    report += "\n";

    ENSURE(!report.empty(), "Device report is empty");
}

void Reporter::generateJobReport(Job *const job) {
    REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
    REQUIRE(report.empty(), "Report should be empty");
    REQUIRE(job->getJobNumber() >= 0, "JobNumber is negative.");
    REQUIRE(job->getPageCount() >= 0, "PageCount is negative.");
    REQUIRE(job->getPrintedPageCount() >=0, "PrintedPageCount is negative");
    REQUIRE(isValidJobType(job->getType()), "Type is not defined");
    REQUIRE(job->getAssignedTo() != NULL, "Device should be assigned");

    report += "[Job #" + std::to_string(job->getJobNumber()) + "]\n";
    report += "* Owner: " + job->getUserName() + "\n";
    report += "* Device: " + job->getAssignedTo()->getName() + "\n";
    if(job->getStatus() == Job::printing){
        report += "* Status: " + std::to_string(job->getPrintedPageCount()) + " pages done\n";
    }
    else if(job->getStatus() == Job::waiting || job->getStatus() == Job::assigned){
        int queueNumber = job->getQueueNumber();
        report += "* Status: WAITING #" + std::to_string(queueNumber + 1) + "\n";
    }
    else if (job->getStatus() == Job::done) {
        report += "* Status: FINISHED\n";
    }
    else {
        report += "* Status: " + std::to_string(job->getStatus()) + "\n";
    }

    report += "* Total pages: " + std::to_string(job->getPageCount()) + " pages\n";
    report += "* Total CO2: " + std::to_string(job->getAssignedTo()->getEmission() * job->getPrintedPageCount()) + "g CO2\n";
    report += "* Total cost: " + std::to_string(job->getAssignedTo()->getCost() * job->getPrintedPageCount()) + " cents\n";

    ENSURE(!report.empty(), "Job report is empty");
}

void Reporter::generateJobFinishReport(Job *const job) {
    REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
    REQUIRE(job != NULL, "Job should not be NULL");
    REQUIRE(report.empty(), "Report should be empty");
    REQUIRE(job->getAssignedTo() != NULL, "Job is not assigned to a device");

    report += "Printer \"" + job->getAssignedTo()->getName() + "\" finished "
            + job->getType() + ":\n";
    report += "\tNumber: " + std::to_string(job->getJobNumber()) + "\n";
    report += "\tSubmitted by \"" + job->getUserName() + "\"\n";
    report += "\t" + std::to_string(job->getPageCount()) + " pages\n";

    ENSURE(!report.empty(), "Job report is empty");
}

void Reporter::generateDeviceAdvancedReport(Device *const device) {
    REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
    REQUIRE(device != NULL, "Device should not be NULL");
    REQUIRE(report.empty(), "Report should be empty");
    report += device->getName() + "\n";
    if(device->getJobs().empty()){
        report += "\t|\n";
        return;
    }
    report += "\t["
            + std::to_string(device->getJobs().front()->getPageCount() - device->getJobs().front()->getPrintedPageCount())
            + "/" + std::to_string(device->getJobs().front()->getPageCount()) + "]\t|";
    for(size_t i = 1; i < device->getJobs().size(); i++){
        report += " [" + std::to_string(device->getJobs()[i]->getPageCount()) + "]";
    }

    report += "\n";
    ENSURE(!report.empty(), "Advance Device report is empty");
}

std::string Reporter::getReport() const {
    REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
    return report;
}

void Reporter::clearReport() {
    REQUIRE(properlyInitialized(), "Reporter should be properlyInitialized");
    report = "";
    ENSURE(report == "", "Report should be empty");
}
