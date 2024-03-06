//
// Created by student on 29/02/24.
//

#include "DesignByContract.h"
#include "Device.h"
#include "utils.h"
#include <iostream>

Device::Device(const std::string &name, int emission, int speed) : name(name), emission(emission), speed(speed) {}

Device::Device(TiXmlElement *device_node) {
    std::string temp_name;
    std::string temp_emission;
    std::string temp_speed;

    for (TiXmlNode *node = device_node->FirstChild(); node != nullptr; node = node->NextSibling()) {
        if (node->FirstChild() == nullptr) {
            std::cerr << "'" << node->Value() << "' is not allowed to be empty" << std::endl;
            continue;
        }
        if (std::string(node->Value()) == "name") {
            temp_name = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "emission") {
            temp_emission = node->FirstChild()->Value();
        } else if (std::string(node->Value()) == "speed") {
            temp_speed = node->FirstChild()->Value();
        } else {
            std::cerr << "Unknown attribute for Device: '" << node->Value() << "'" << std::endl;
        }
    }

    ENSURE(!temp_name.empty(), "No name is provided");
    ENSURE(!temp_emission.empty(), "No emission is provided");
    ENSURE(is_number(temp_emission) , "Emission should be a number");
    ENSURE(!temp_speed.empty(), "No speed is provided");
    ENSURE(is_number(temp_speed) , "Speed should be a number");

    name = temp_name;
    emission = std::stoi(temp_emission);
    speed = std::stoi(temp_speed);
    init_ = this;
}
