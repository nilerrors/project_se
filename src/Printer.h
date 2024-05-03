//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_PRINTER_H
#define PRINTSYSTEM_PRINTER_H

#include "Device.h"

class Printer : public Device {
public:
    /**
     * \brief Constructor for Printer
     * @param name
     * @param emission
     * @param speed
     */
    Printer(const std::string &name, int emission, int speed, int cost);

    /**
     * \brief Destructor for Printer
     */
    ~Printer() override;

    /**
     * \brief Get type of device
     * @return
     * @require
     * - REQUIRE(properlyInitialized(), "Printer is not properly initialized.");
     */
    std::string getType() override = 0;
};


#endif //PRINTSYSTEM_PRINTER_H
