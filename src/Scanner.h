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
     * \param device_element TiXmlElement containing the device data
     * \return A new Device object

     * @expect
        - EXPECT(!temp_name.empty(), "No name is provided");
        - EXPECT(!temp_emission.empty(), "No emission is provided");
        - EXPECT(is_number(temp_emission) , "Emission should be an integer number");
        - EXPECT(!temp_speed.empty(), "No speed is provided");
        - EXPECT(is_number(temp_speed) , "Speed should be an integer number");
     */
    explicit Scanner(TiXmlElement *scanner_element);

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
