//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_SCANNER_H
#define PRINTSYSTEM_SCANNER_H


#include "Device.h"

class Scanner : public Device {
public:
    /**
     * \brief Constructor for Device
     * @param name
     * @param emission
     * @param speed
     */
    Scanner(const std::string &name, int emission, int speed, int cost);

    ~Scanner() override;

    std::string getType() override;
};


#endif //PRINTSYSTEM_SCANNER_H
