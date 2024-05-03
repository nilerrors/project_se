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

    ~PrinterBlackWhite() override;

    std::string getType() override;
};


#endif //PRINTSYSTEM_PRINTERBLACKWHITE_H
