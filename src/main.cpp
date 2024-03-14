#include "DesignByContract.h"
#include "System.h"
#include <iostream>

/**
 * Eenvoudige main functie.
 */
int main(int argc, const char *argv[])
{
    System system;
    system.ReadData("xml_tests/ReportHD.xml");
    system.getDevices().front()->addJob(system.getFirstJob());
    system.getDevices().front()->addJob(system.getJobs()[1]);
    system.getDevices().front()->addJob(system.getJobs()[2]);
    system.getDevices().front()->addJob(system.getJobs().back());
    std::cout << system.printReport() << std::endl;

    return 0;
}
