#include "lib/DesignByContract.h"
#include "System.h"
#include <iostream>

/**
 * Eenvoudige main functie.
 */
int main(int argc, const char *argv[])
{
    System system;
    system.ReadData("xml_tests/ReportHD.xml");
    system.processAll();
    std::cout << system.printReport() << std::endl;

    return 0;
}
