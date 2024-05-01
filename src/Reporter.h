//
// Created by nilerrors on 5/1/24.
//

#ifndef PRINTSYSTEM_REPORTER_H
#define PRINTSYSTEM_REPORTER_H

#include <string>

class Device;
class Job;

class Reporter {
public:
    virtual void generateDeviceReport(Device *const device);

    virtual void generateJobReport(Job *const job);

    virtual void generateJobFinishReport(Job *const job);

    virtual void generateDeviceAdvancedReport(Device *const device);

    std::string getReport() const;

    void clearReport();

private:
    std::string report;
};


#endif //PRINTSYSTEM_REPORTER_H
