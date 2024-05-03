//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_PRINTERCOLOR_H
#define PRINTSYSTEM_PRINTERCOLOR_H

#include "Printer.h"

class PrinterColor : public Printer {
public:
    /**
     * \brief Constructor for Printer
     * @param name
     * @param emission
     * @param speed
     */
    PrinterColor(const std::string &name, int emission, int speed, int cost);

    /**
     * \brief Destructor for PrinterColor
     */
    ~PrinterColor() override;

    /**
     * \brief Get type of printer
     * @return
     * @require
     * - REQUIRE(properlyInitialized(), "Color Printer is not properly initialized.");
     */
    std::string getType() override;
};


#endif //PRINTSYSTEM_PRINTERCOLOR_H
