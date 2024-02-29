#include "DesignByContract.h"
#include "System.h"

/**
 * Eenvoudige main functie.
 */
int main(int argc, const char *argv[])
{
    System system;
    system.ReadData("xml_examples/SystemExample.xml");

    return 0;
}
