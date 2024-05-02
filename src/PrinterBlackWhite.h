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
     * \param device_element TiXmlElement containing the device data
     * \return A new Device object

     * @expect
        - EXPECT(!temp_name.empty(), "No name is provided");
        - EXPECT(!temp_emission.empty(), "No emission is provided");
        - EXPECT(is_number(temp_emission) , "Emission should be an integer number");
        - EXPECT(!temp_speed.empty(), "No speed is provided");
        - EXPECT(is_number(temp_speed) , "Speed should be an integer number");
     */
    explicit PrinterBlackWhite(TiXmlElement *device_element);

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
