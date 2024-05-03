//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_SCANNER_H
#define PRINTSYSTEM_SCANNER_H


#include "Device.h"

class Scanner : public Device {
public:
    /**
     * \brief Constructor for Scanner
     * @param name
     * @param emission
     * @param speed
     */
    Scanner(const std::string &name, int emission, int speed, int cost);

    /**
     * \brief Destructor for Scanner
     */
    ~Scanner() override;

    /**
     * \brief Get type of Scanner
     * @return
     * @require
     * - REQUIRE(properlyInitialized(), "Scanner is not properly initialized.");
     */
    std::string getType() override;
};


#endif //PRINTSYSTEM_SCANNER_H
