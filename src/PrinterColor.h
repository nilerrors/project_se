//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_PRINTERCOLOR_H
#define PRINTSYSTEM_PRINTERCOLOR_H

#include "Printer.h"

class PrinterColor : public Printer {
public:
    /**
     * \brief Constructor for Device
     * @param name
     * @param emission
     * @param speed
     */
    PrinterColor(const std::string &name, int emission, int speed, int cost);

    ~PrinterColor() override;

    std::string getType() override;
};


#endif //PRINTSYSTEM_PRINTERCOLOR_H
