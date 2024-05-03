//
// Created by student on 2/05/24.
//

#ifndef PRINTSYSTEM_DEVICEFACTORY_H
#define PRINTSYSTEM_DEVICEFACTORY_H

#include "Device.h"

class DeviceFactory {
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
    explicit DeviceFactory(TiXmlElement *device_element);

    /**
     * \brief Checks if the class is properly initialized
     * @return A boolean indicating if the class is properly initialized
     */
    bool properlyInitialized() const { return init_ == this; }


    /**
     * \brief Get Device
     * @return A pointer to the Device
     * @require
     * - REQUIRE(properlyInitialized(), "DeviceFactory is not properly initialized.");
     */
    Device *getDevice() const;

private:
    Device *device = nullptr;
    DeviceFactory *init_ = this;
};


#endif //PRINTSYSTEM_DEVICEFACTORY_H
