//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_PRINTERBLACKWHITE_H
#define PRINTSYSTEM_PRINTERBLACKWHITE_H

#include "Printer.h"

class PrinterBlackWhite : public Printer {
public:
    /**
     * \brief Constructor for Device
     * @param name
     * @param emission
     * @param speed
     */
    PrinterBlackWhite(const std::string &name, int emission, int speed, int cost);

    /**
     * \brief Destructor for PrinterBlackWhite
     */
    ~PrinterBlackWhite() override;

    /**
     * \brief Get type of printer
     * @return
     * @require
     * - REQUIRE(properlyInitialized(), "Black and White Printer is not properly initialized.");
     */
    std::string getType() override;
};


#endif //PRINTSYSTEM_PRINTERBLACKWHITE_H
