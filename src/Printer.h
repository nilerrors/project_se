//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_PRINTER_H
#define PRINTSYSTEM_PRINTER_H

#include "Device.h"

class Printer : public Device {
public:
    /**
     * \brief Constructor for Device
     * @param name
     * @param emission
     * @param speed
     */
    Printer(const std::string &name, int emission, int speed, int cost);

    ~Printer() override;

    std::string getType() override = 0;
};


#endif //PRINTSYSTEM_PRINTER_H
